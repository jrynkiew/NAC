#include "renderer.h"

namespace NAC
{
	Renderer* Renderer::m_pInstance;

	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	Renderer* Renderer::GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new Renderer();

		return m_pInstance;
	}

	// void Renderer::Initialize()
	// {
	// 	// ImGuiIO& io = ImGui::GetIO();

	// 	// io.Fonts->AddFontFromMemoryTTF(g_fFont, sizeof(g_fFont), 14.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	// 	// m_pFont = io.Fonts->AddFontFromMemoryTTF(g_fFont, sizeof(g_fFont), 32.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	// }

	void Renderer::BeginScene()
	{
		ImVec2 window_pos = ImGui::GetWindowPos(); 
        ImVec2 window_size = ImGui::GetWindowSize(); 
        ImVec2 window_center = ImVec2(window_pos.x + window_size.x * 0.5f, window_pos.y + window_size.y * 0.5f); 
        ImGui::GetBackgroundDrawList()->AddCircle(window_center, window_size.x * 0.6f, IM_COL32(255, 0, 0, 200), 0, 10 + 4); 
        ImGui::GetForegroundDrawList()->AddCircle(window_center, window_size.y * 0.6f, IM_COL32(0, 255, 0, 200), 0, 10);
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        static float sz = 36.0f; 
        static float thickness = 4.0f; 
        static ImVec4 col = ImVec4(1.0f, 1.0f, 0.4f, 1.0f); 
        const ImVec2 p = ImGui::GetCursorScreenPos(); 
        const ImU32 col32 = ImColor(col); 
        float x = p.x + 4.0f, y = p.y + 4.0f;
        draw_list->AddCircle(ImVec2(x+sz*0.5f, y+sz*0.5f), sz*0.5f, col32, 6, thickness);
		// Rendering
       
		// ImGuiIO& io = ImGui::GetIO();

		// ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		// ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		// ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
		// ImGui::Begin("##Backbuffer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

		// ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		// ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);
	}

	// void Renderer::EndScene()
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();
	// 	window->DrawList->PushClipRectFullScreen();

	// 	ImGui::End();
	// 	ImGui::PopStyleColor();
	// 	ImGui::PopStyleVar(2);
	// }

	// float Renderer::RenderText(const std::string& text, const ImVec2& position, float size, uint32_t color, bool center)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xff;
	// 	float r = (color >> 16) & 0xff;
	// 	float g = (color >> 8) & 0xff;
	// 	float b = (color) & 0xff;

	// 	std::stringstream stream(text);
	// 	std::string line;

	// 	float y = 0.0f;
	// 	int i = 0;

	// 	while (std::getline(stream, line))
	// 	{
	// 		ImVec2 textSize = m_pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

	// 		if (center)
	// 		{
	// 			window->DrawList->AddText(m_pFont, size, { (position.x - textSize.x / 2.0f) + 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	// 			window->DrawList->AddText(m_pFont, size, { (position.x - textSize.x / 2.0f) - 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	// 			window->DrawList->AddText(m_pFont, size, { (position.x - textSize.x / 2.0f) + 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	// 			window->DrawList->AddText(m_pFont, size, { (position.x - textSize.x / 2.0f) - 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());

	// 			window->DrawList->AddText(m_pFont, size, { position.x - textSize.x / 2.0f, position.y + textSize.y * i }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), line.c_str());
	// 		}
	// 		else
	// 		{
	// 			window->DrawList->AddText(m_pFont, size, { (position.x) + 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	// 			window->DrawList->AddText(m_pFont, size, { (position.x) - 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	// 			window->DrawList->AddText(m_pFont, size, { (position.x) + 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	// 			window->DrawList->AddText(m_pFont, size, { (position.x) - 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());

	// 			window->DrawList->AddText(m_pFont, size, { position.x, position.y + textSize.y * i }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), line.c_str());
	// 		}

	// 		y = position.y + textSize.y * (i + 1);
	// 		i++;
	// 	}

	// 	return y;
	// }

	// void Renderer::RenderLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xff;
	// 	float r = (color >> 16) & 0xff;
	// 	float g = (color >> 8) & 0xff;
	// 	float b = (color) & 0xff;

	// 	window->DrawList->AddLine(from, to, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), thickness);
	// }

	// void Renderer::RenderCircle(const ImVec2& position, float radius, uint32_t color, float thickness, uint32_t segments)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xff;
	// 	float r = (color >> 16) & 0xff;
	// 	float g = (color >> 8) & 0xff;
	// 	float b = (color) & 0xff;

	// 	window->DrawList->AddCircle(position, radius, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), segments, thickness);
	// }

	// void Renderer::RenderCircleFilled(const ImVec2& position, float radius, uint32_t color, uint32_t segments)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xff;
	// 	float r = (color >> 16) & 0xff;
	// 	float g = (color >> 8) & 0xff;
	// 	float b = (color) & 0xff;

	// 	window->DrawList->AddCircleFilled(position, radius, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), segments);
	// }

	// void Renderer::RenderRect(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding, uint32_t roundingCornersFlags, float thickness)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xFF;
	// 	float r = (color >> 16) & 0xFF;
	// 	float g = (color >> 8) & 0xFF;
	// 	float b = (color) & 0xFF;

	// 	window->DrawList->AddRect(from, to, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), rounding, roundingCornersFlags, thickness);
	// }

	// void Renderer::RenderRectFilled(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding, uint32_t roundingCornersFlags)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xFF;
	// 	float r = (color >> 16) & 0xFF;
	// 	float g = (color >> 8) & 0xFF;
	// 	float b = (color) & 0xFF;

	// 	window->DrawList->AddRectFilled(from, to, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), rounding, roundingCornersFlags);
	// }

	// void Renderer::RenderImage(GLuint * pTexture, const ImVec2& from, const ImVec2& to, uint32_t color)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xFF;
	// 	float r = (color >> 16) & 0xFF;
	// 	float g = (color >> 8) & 0xFF;
	// 	float b = (color) & 0xFF;

	// 	window->DrawList->AddImage(pTexture, from, to, { 0.0f, 0.0f }, { 1.0f, 1.0f }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }));
	// }

	// void Renderer::RenderImageRounded(GLuint * pTexture, const ImVec2& from, const ImVec2& to, uint32_t color, float rounding, uint32_t roundingCornersFlags)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xFF;
	// 	float r = (color >> 16) & 0xFF;
	// 	float g = (color >> 8) & 0xFF;
	// 	float b = (color) & 0xFF;

	// 	window->DrawList->AddImageRounded(pTexture, from, to, { 0.0f, 0.0f }, { 1.0f, 1.0f }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), rounding, roundingCornersFlags);
	// }
}