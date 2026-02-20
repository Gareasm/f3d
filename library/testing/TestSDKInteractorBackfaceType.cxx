#include "PseudoUnitTest.h"

#include <engine.h>
#include <interactor.h>
#include <options.h>
#include <scene.h>

int TestSDKInteractorBackfaceType(int argc, char* argv[])
{
  PseudoUnitTest test;

  f3d::engine eng = f3d::engine::create(true);
  f3d::scene& sce = eng.getScene();
  f3d::interactor& inter = eng.getInteractor();
  f3d::options& opts = eng.getOptions();

  sce.add(std::string(argv[1]) + "/data/cow.vtp");

  // initial state is default (nullopt)
  test("initial backface.type is nullopt (default)", !opts.render.backface.type.has_value());

  // first cycle → "visible"
  inter.triggerCommand("cycle_backface_type");
  test("after 1st cycle backface.type is 'visible'",
    opts.render.backface.type.has_value() && *opts.render.backface.type == "visible");

  // second cycle → "hidden"
  inter.triggerCommand("cycle_backface_type");
  test("after 2nd cycle backface.type is 'hidden'",
    opts.render.backface.type.has_value() && *opts.render.backface.type == "hidden");

  // third cycle → back to nullopt (default)
  inter.triggerCommand("cycle_backface_type");
  test("after 3rd cycle backface.type is nullopt (default) again",
    !opts.render.backface.type.has_value());

  return test.result();
}