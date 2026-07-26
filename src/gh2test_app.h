// gh2test - ReXGlue Recompiled Project
//
// This file is yours to edit. 'rexglue migrate' will NOT overwrite it.
// Customize your app by overriding virtual hooks from rex::ReXApp.

#pragma once

#include <rex/rex_app.h>

class Gh2testApp : public rex::ReXApp {
 public:
  using rex::ReXApp::ReXApp;

  static std::unique_ptr<rex::ui::WindowedApp> Create(
      rex::ui::WindowedAppContext& ctx) {
    return std::unique_ptr<Gh2testApp>(new Gh2testApp(ctx, "gh2test",
        PPCImageConfig));
  }

  // Override virtual hooks for customization:
  void OnPreSetup(rex::RuntimeConfig& config) override {
    //auto graphics = config.graphics.get();
    REXLOG_INFO("HELLO!!!\n");
  }

  // void OnLoadXexImage(std::string& xex_image) override {}
  void OnPostSetup() override {
    REXLOG_INFO("HELLO POSTY!!!\n");

  }
  // void OnCreateDialogs(rex::ui::ImGuiDrawer* drawer) override {}
  // void OnShutdown() override {}
  // void OnConfigurePaths(rex::PathConfig& paths) override {}
};
