#include "interface.h"

namespace _NAC
{
    Interface* Interface::m_pInstance = nullptr;
    GLFWwindow* Interface::m_pWindow = nullptr;
    ImGuiContext* Interface::m_pImGuiContext = nullptr;
    ImGuiIO* Interface::m_pImGuiIO = nullptr;
    ImGuiStyle* Interface::m_pImGuiStyle = nullptr;

    Interface::Interface() {
        // IMGUI_CHECKVERSION();
		// ImGui::CreateContext();
        // m_pImGuiIO = &ImGui::GetIO(); (void)m_pImGuiIO;
        // m_pImGuiStyle = &ImGui::GetStyle();
        // m_pImGuiColors = m_pImGuiStyle->Colors;
    }

    Interface::~Interface() {
    }

    bool Interface::Initialize(GLFWwindow* window) {
        IMGUI_CHECKVERSION();
		ImGui::CreateContext();

        m_pImGuiIO = &ImGui::GetIO(); (void)m_pImGuiIO;
        m_pImGuiStyle = &ImGui::GetStyle();

        SetConfig();
        SetStyle();

        // m_pWindow = window;
		// ImGui_ImplGlfw_InitForOpenGL(window, true);

		// #ifdef __EMSCRIPTEN__
		// 	ImGui_ImplOpenGL3_Init("#version 300 es");
		// #else
		// 	ImGui_ImplOpenGL3_Init("#version 410 core");
		// #endif

        return true;
    }

    void Interface::SetStyle() {
        m_pImGuiStyle->Colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TextDisabled]           = ImVec4(0.35f, 0.44f, 0.27f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_WindowBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
		m_pImGuiStyle->Colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		m_pImGuiStyle->Colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		m_pImGuiStyle->Colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.86f, 0.61f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_BorderShadow]           = ImVec4(0.06f, 0.94f, 0.53f, 0.56f);
		m_pImGuiStyle->Colors[ImGuiCol_FrameBg]                = ImVec4(0.15f, 0.15f, 0.15f, 0.56f);
		m_pImGuiStyle->Colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.00f, 0.86f, 0.61f, 0.23f);
		m_pImGuiStyle->Colors[ImGuiCol_FrameBgActive]          = ImVec4(0.33f, 0.53f, 0.34f, 0.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TitleBgActive]          = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_MenuBarBg]              = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_SliderGrab]             = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_SliderGrabActive]       = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_Button]                 = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ButtonHovered]          = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ButtonActive]           = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.67f);
		m_pImGuiStyle->Colors[ImGuiCol_HeaderHovered]          = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_HeaderActive]           = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_Separator]              = ImVec4(0.35f, 0.44f, 0.27f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.18f, 0.23f, 0.20f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_SeparatorActive]        = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ResizeGrip]             = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_Tab]                    = ImVec4(1.00f, 0.74f, 0.00f, 0.12f);
		m_pImGuiStyle->Colors[ImGuiCol_TabHovered]             = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TabActive]              = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.97f);
		m_pImGuiStyle->Colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.01f, 0.77f, 0.46f, 0.16f);
		m_pImGuiStyle->Colors[ImGuiCol_DockingPreview]         = ImVec4(0.26f, 0.59f, 0.98f, 0.22f);
		m_pImGuiStyle->Colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.78f, 0.87f, 0.98f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.57f, 0.57f, 0.64f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TableBorderLight]       = ImVec4(0.68f, 0.68f, 0.74f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TableRowBgAlt]          = ImVec4(0.30f, 0.30f, 0.30f, 0.09f);
		m_pImGuiStyle->Colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		m_pImGuiStyle->Colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		m_pImGuiStyle->Colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		m_pImGuiStyle->Colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		m_pImGuiStyle->Colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

        m_pImGuiStyle->WindowPadding = ImVec2(15.0f, 15.0f);
		m_pImGuiStyle->FrameRounding = 3.0f;
		m_pImGuiStyle->ItemSpacing = ImVec2(6.0f, 6.0f);
    }

    void Interface::SetConfig() {
		m_pImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		m_pImGuiIO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		#ifndef __EMSCRIPTEN__
			m_pImGuiIO->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			if (m_pImGuiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				m_pImGuiStyle->WindowRounding = 0.0f;
				m_pImGuiStyle->Colors[ImGuiCol_WindowBg].w = 1.0f;
			}
		#endif
    }

    void Interface::Shutdown() {
    }

    void Interface::Draw() {
    }

    Interface* Interface::GetInstance() {
        if (!m_pInstance)
            m_pInstance = new Interface();

        return m_pInstance;
    }

    GLFWwindow* Interface::GetWindow() {
        return m_pWindow;
    }

    ImGuiContext* Interface::GetImGuiContext() {
        return m_pImGuiContext;
    }

    ImGuiIO* Interface::GetImGuiIO() {
        return m_pImGuiIO;
    }

    ImGuiStyle* Interface::GetImGuiStyle() {
        return m_pImGuiStyle;
    }
}

