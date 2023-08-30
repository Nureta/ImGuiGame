#include <bits/stdc++.h>
#include <Windows.h>
#include "guistuff.cpp"
#include <stdint.h>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <chrono>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
/*----------------------------------------------------------------------------
//TODO:
//Add static numbers to items to avoid weird combos
//make this file cleaner
//Change title and name this game
//Make changes with encounter levels
//DEBUGGING WINDOW REMOVE WHEN OVER
----------------------------------------------------------------------------*/


bool encounterWindow = false;
std::vector<encounterDisplay*>EncounterVec;


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}


void delay()
{
    auto start = std::chrono::high_resolution_clock::now();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    while (true)
    {
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        if (duration.count() >= 12000)
        {
            return;
        }
        else
            continue;
    }
}

//randomize in place and change style
//can make multiple appear at once with loops for every encounter. may be laggy but you prob should've killed everyhting






void SetupImGuiStyle()
{
    // MyTheme style from ImThemes
    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.6000000238418579f;
    style.WindowPadding = ImVec2(11.5f, 7.400000095367432f);
    style.WindowRounding = 0.0f;
    style.WindowBorderSize = 1.0f;
    style.WindowMinSize = ImVec2(32.0f, 32.0f);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.ChildRounding = 0.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 13.60000038146973f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(4.0f, 3.0f);
    style.FrameRounding = 3.5f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(8.0f, 4.0f);
    style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
    style.CellPadding = ImVec2(4.0f, 2.0f);
    style.IndentSpacing = 21.0f;
    style.ColumnsMinSpacing = 6.0f;
    style.ScrollbarSize = 14.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabMinSize = 10.0f;
    style.GrabRounding = 2.799999952316284f;
    style.TabRounding = 6.400000095367432f;
    style.TabBorderSize = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    style.Colors[ImGuiCol_Text] = ImVec4(9.999999974752427e-07f, 9.999899930335232e-07f, 9.999899930335232e-07f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4206008315086365f, 0.4205966293811798f, 0.4205966293811798f, 1.0f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.9527897238731384f, 0.9527801871299744f, 0.9527801871299744f, 0.9270386099815369f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.3562195897102356f, 0.3562195897102356f, 0.3562231659889221f, 0.9200000166893005f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 0.5f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.4206008315086365f, 0.4205966293811798f, 0.4205966293811798f, 0.0f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4274509847164154f, 0.3899999856948853f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3433442413806915f, 0.3433442413806915f, 0.3433476686477661f, 0.4000000059604645f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.3733870387077332f, 0.3733868300914764f, 0.3733905553817749f, 0.6899999976158142f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.7811080813407898f, 0.7811080813407898f, 0.7811158895492554f, 0.8299999833106995f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.4763900637626648f, 0.4763900637626648f, 0.4763948321342468f, 0.8700000047683716f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.2231737077236176f, 0.2231759428977966f, 0.223175123333931f, 0.9871244430541992f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.5278916954994202f, 0.5278916954994202f, 0.5278970003128052f, 0.800000011920929f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.6180195808410645f, 0.618022620677948f, 0.6180257797241211f, 0.6000000238418579f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.4549310505390167f, 0.4549310505390167f, 0.454935610294342f, 0.300000011920929f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4720982611179352f, 0.4720982611179352f, 0.4721029996871948f, 0.4000000059604645f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5965612530708313f, 0.5965605974197388f, 0.5965665578842163f, 0.6000000238418579f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.184547483921051f, 0.184548631310463f, 0.1845493316650391f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.5150162577629089f, 0.5150194764137268f, 0.5150214433670044f, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.296134352684021f, 0.296136200428009f, 0.2961373329162598f, 1.0f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.592268705368042f, 0.5922707319259644f, 0.5922746658325195f, 0.6200000047683716f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.9531213045120239f, 0.9628169536590576f, 0.991416335105896f, 0.7900000214576721f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.6781047582626343f, 0.6781063675880432f, 0.6781115531921387f, 1.0f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.5836851596832275f, 0.5836851596832275f, 0.5836910009384155f, 0.449999988079071f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.4495938420295715f, 0.4495940804481506f, 0.4635193347930908f, 0.800000011920929f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.6566457748413086f, 0.6566457748413086f, 0.6566523313522339f, 0.800000011920929f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.5364806652069092f, 0.5364753007888794f, 0.5364753007888794f, 0.6000000238418579f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.6000000238418579f, 0.6000000238418579f, 0.6980392336845398f, 1.0f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.6980392336845398f, 0.6980392336845398f, 0.8980392217636108f, 1.0f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.0f, 1.0f, 1.0f, 0.1000000014901161f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.7764706015586853f, 0.8196078538894653f, 1.0f, 0.6000000238418579f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.7764706015586853f, 0.8196078538894653f, 1.0f, 0.8999999761581421f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.5708097219467163f, 0.5708097219467163f, 0.5708154439926147f, 0.7860000133514404f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.4248884618282318f, 0.4248884618282318f, 0.4248927235603333f, 0.800000011920929f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.7467736601829529f, 0.7467736601829529f, 0.7467811107635498f, 0.8420000076293945f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.4720982611179352f, 0.4720982611179352f, 0.4721029996871948f, 0.8212000131607056f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.3133015930652618f, 0.3133015930652618f, 0.3133047223091125f, 0.8371999859809875f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.2875507771968842f, 0.2875507771968842f, 0.2875536680221558f, 1.0f);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.5536425113677979f, 0.5536425113677979f, 0.553648054599762f, 1.0f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.5235998630523682f, 0.5235998630523682f, 0.5236051082611084f, 1.0f);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.4892703890800476f, 0.489265501499176f, 0.489265501499176f, 0.0f);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.07000000029802322f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.489265501499176f, 0.489265501499176f, 0.4892703890800476f, 0.3499999940395355f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.4806818962097168f, 0.4806818962097168f, 0.4806867241859436f, 0.800000011920929f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.3605149984359741f, 0.3605113923549652f, 0.3605113923549652f, 0.3499999940395355f);
}

void DarkSetupImGuiStyle()
{
    // DarkTheme style from ImThemes
    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.6000000238418579f;
    style.WindowPadding = ImVec2(11.5f, 7.400000095367432f);
    style.WindowRounding = 0.0f;
    style.WindowBorderSize = 1.0f;
    style.WindowMinSize = ImVec2(32.0f, 32.0f);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.ChildRounding = 0.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 13.60000038146973f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(4.0f, 3.0f);
    style.FrameRounding = 3.5f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(8.0f, 4.0f);
    style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
    style.CellPadding = ImVec2(4.0f, 2.0f);
    style.IndentSpacing = 21.0f;
    style.ColumnsMinSpacing = 6.0f;
    style.ScrollbarSize = 14.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabMinSize = 10.0f;
    style.GrabRounding = 2.799999952316284f;
    style.TabRounding = 6.400000095367432f;
    style.TabBorderSize = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    style.Colors[ImGuiCol_Text] = ImVec4(0.6223175525665283f, 0.6223112940788269f, 0.6223112940788269f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4206008315086365f, 0.4205966293811798f, 0.4205966293811798f, 1.0f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1072961091995239f, 0.107295036315918f, 0.107295036315918f, 0.9270386099815369f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.2532188892364502f, 0.2532163560390472f, 0.2532163560390472f, 0.0f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.2188819199800491f, 0.2188819199800491f, 0.2188841104507446f, 0.9200000166893005f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.1888412237167358f, 0.1888393312692642f, 0.1888393312692642f, 0.5f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.1459227204322815f, 0.1459212601184845f, 0.1459212601184845f, 0.0f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.2446351647377014f, 0.2446327209472656f, 0.2446327209472656f, 0.3899999856948853f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2274655550718307f, 0.2274655550718307f, 0.2274678349494934f, 0.4000000059604645f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.1974232941865921f, 0.1974229067564011f, 0.1974248886108398f, 0.6899999976158142f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.124462254345417f, 0.124462254345417f, 0.1244634985923767f, 0.8299999833106995f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.2060065567493439f, 0.2060065567493439f, 0.2060086131095886f, 0.8700000047683716f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.2231737077236176f, 0.2231759428977966f, 0.223175123333931f, 0.9871244430541992f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1759639084339142f, 0.1759639084339142f, 0.1759656667709351f, 0.800000011920929f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.5021408796310425f, 0.5021437406539917f, 0.5021458864212036f, 0.6000000238418579f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1459212601184845f, 0.1459212601184845f, 0.1459227204322815f, 0.300000011920929f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.2060065567493439f, 0.2060065567493439f, 0.2060086131095886f, 0.4000000059604645f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1888395845890045f, 0.1888393312692642f, 0.1888412237167358f, 0.6000000238418579f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.7668219804763794f, 0.7730331420898438f, 0.7768239974975586f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.5150162577629089f, 0.5150194764137268f, 0.5150214433670044f, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.296134352684021f, 0.296136200428009f, 0.2961373329162598f, 1.0f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.2274655550718307f, 0.2274664789438248f, 0.2274678349494934f, 0.6200000047683716f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.4248884618282318f, 0.4248895347118378f, 0.4248927235603333f, 0.7900000214576721f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.3218851685523987f, 0.3218859434127808f, 0.3218883872032166f, 1.0f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.1974229067564011f, 0.1974229067564011f, 0.1974248886108398f, 0.449999988079071f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.1759639084339142f, 0.1759639084339142f, 0.1759656667709351f, 0.800000011920929f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.1888393312692642f, 0.1888393312692642f, 0.1888412237167358f, 0.800000011920929f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.5364806652069092f, 0.5364753007888794f, 0.5364753007888794f, 0.6000000238418579f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.6000000238418579f, 0.6000000238418579f, 0.6980392336845398f, 1.0f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.6980392336845398f, 0.6980392336845398f, 0.8980392217636108f, 1.0f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.0f, 1.0f, 1.0f, 0.1000000014901161f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.7764706015586853f, 0.8196078538894653f, 1.0f, 0.6000000238418579f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.7764706015586853f, 0.8196078538894653f, 1.0f, 0.8999999761581421f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.2060065567493439f, 0.2060065567493439f, 0.2060086131095886f, 0.7860000133514404f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.2746753692626953f, 0.2746753692626953f, 0.274678111076355f, 0.800000011920929f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.1545048952102661f, 0.1545048952102661f, 0.1545064449310303f, 0.8420000076293945f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.2017146944999695f, 0.2017146944999695f, 0.2017167210578918f, 0.8212000131607056f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.3133015930652618f, 0.3133015930652618f, 0.3133047223091125f, 0.8371999859809875f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.2875507771968842f, 0.2875507771968842f, 0.2875536680221558f, 1.0f);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.5536425113677979f, 0.5536425113677979f, 0.553648054599762f, 1.0f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.5235998630523682f, 0.5235998630523682f, 0.5236051082611084f, 1.0f);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.4892703890800476f, 0.489265501499176f, 0.489265501499176f, 0.0f);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.07000000029802322f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.489265501499176f, 0.489265501499176f, 0.4892703890800476f, 0.3499999940395355f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.4806818962097168f, 0.4806818962097168f, 0.4806867241859436f, 0.800000011920929f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.3605149984359741f, 0.3605113923549652f, 0.3605113923549652f, 0.3499999940395355f);
}

// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;


#if defined(IMGUI_IMPL_OPENGL_ES2)

    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
  
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           
#else
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

#endif
    float WindowWidth = 1080.f;
    float WindowHeight = 1920.f;
    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(WindowHeight, WindowWidth, "Game", nullptr, nullptr);
    if (window == nullptr)
        return 1;

    glfwSetWindowSizeLimits(window, 800, 400, 2560, 1440);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();



    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    io.Fonts->AddFontDefault();



     /*----------------------------------------------------------------------------
     ███╗   ███╗ █████╗ ██╗███╗   ██╗    ███████╗████████╗██╗   ██╗███████╗███████╗
     ████╗ ████║██╔══██╗██║████╗  ██║    ██╔════╝╚══██╔══╝██║   ██║██╔════╝██╔════╝
     ██╔████╔██║███████║██║██╔██╗ ██║    ███████╗   ██║   ██║   ██║█████╗  █████╗
     ██║╚██╔╝██║██╔══██║██║██║╚██╗██║    ╚════██║   ██║   ██║   ██║██╔══╝  ██╔══╝
     ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║    ███████║   ██║   ╚██████╔╝██║     ██║
     ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝    ╚══════╝   ╚═╝    ╚═════╝ ╚═╝     ╚═╝
     -----------------------------------------------------------------------------*/
    srand((unsigned)time(NULL));
    Player player;








    // Our state
    bool mainWindow = true;
    bool statWindow = false;
    bool inventoryWindow = false;
    bool debuggingWindow = false;
    bool settingWindow = false;
    //static const char* resArr[4] = { "640 x 480","800 x 600","1280 x 720", "1920 x 1080" };

    ImVec4 clear_color = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    SetupImGuiStyle();

    // Main loop
#ifdef __EMSCRIPTEN__
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif

    {
        delay();
        healthChecker();
        levelUpChecker();
        //Checks for levels lel

        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if (mainWindow)
        {
            
            ImGui::Begin("Menu");                          

            ImGui::Text("This is some useful text.");               
            ImGui::Checkbox("Main Window", &mainWindow);      
            ImGui::Checkbox("Stat", &statWindow);
            ImGui::Checkbox("Debug Window", &debuggingWindow);
            ImGui::Checkbox("Iventory", &inventoryWindow);
            ImGui::Checkbox("Settings", &settingWindow);



            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }
        if (inventoryWindow) {
            ImGui::Begin("Inventory", &inventoryWindow);

            inventoryUi();
            ImGui::End();

        }
        if (statWindow)
        {
            ImGui::Begin("Stat", &statWindow);
             statText();
   
         
            ImGui::End();
        }

        if (settingWindow) {
            ImGui::Begin("Settings", &settingWindow);
            if (ImGui::Button("Dark Mode")) {
                DarkSetupImGuiStyle();
            }
            if (ImGui::Button("Light Mode")) {
                SetupImGuiStyle();
            }
            ImGui::End();


        }
        if (debuggingWindow)
        {
            ImGui::Begin("Debug", &debuggingWindow);
            static int mobLevel;
            ImGui::SliderInt("Level", &mobLevel, 1, 50);
            if (ImGui::Button("Spawn Mob")) {
                encounterDisplay* newEncounter = new encounterDisplay(mobLevel,window);
                mobLevel = charc->level;

                EncounterVec.push_back(newEncounter);
          
            }
            if (ImGui::Button("New Player")) {
                Player Newplayer;
            }

            if (ImGui::Button("Give item")) {
                int roll = rand() % 4;
                item Item(roll);
                charc->inv->items.push_back(Item);
            }

            if (ImGui::Button("Close"))
                debuggingWindow = false;
            ImGui::End();
        }
       

        
        if (!EncounterVec.empty()) {
            for (int i = 0; i < EncounterVec.size(); i++) {
                if (EncounterVec[i] != NULL and EncounterVec[i]->closeWindow != true) {
                    EncounterVec[i]->EncounterDisplayer(i);
                
                }
            }
        }
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
    }











