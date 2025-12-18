/*
    theme.h: Centralized UI styling configuration for Instant Meshes
*/

#pragma once

#include <nanogui/common.h>

struct Theme {
    // High contrast button colors (Alpha increased from 25 -> 100 for visibility)
    static constexpr int ButtonAlpha = 100;
    
    static nanogui::Color greenBtn() { return nanogui::Color(0, 255, 0, ButtonAlpha); }
    static nanogui::Color redBtn() { return nanogui::Color(180, 0, 0, ButtonAlpha); } // Increased red intensity
    static nanogui::Color blueBtn() { return nanogui::Color(0, 50, 255, ButtonAlpha); }
};
