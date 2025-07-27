bool Android_LoadSystemFont(){
    char path[64] {0};
    char *filename = nullptr;
    const char *fontPath[] = {"/system/fonts", "/system/font", "/data/fonts"};
    for (auto tmp:fontPath)
    {
        if (access(tmp, R_OK) == 0)
        {
            strcpy(path, tmp);
            filename = path + strlen(tmp);
            break;
        }
    }
    if (!filename)
    {
        return false;
    }
    *filename++ = '/';
    strcpy(filename, "NotoSansCJK-Regular.ttc");
    if (access(path, R_OK) != 0)
    {
        strcpy(filename, "NotoSerifCJK-Regular.ttc");
        if (access(path, R_OK) != 0)
        {
            return false;
        }
    }
    ImGuiIO *Io = &ImGui::GetIO();
    static ImVector<ImWchar>RanGes;
    if (RanGes.empty())
    {
        ImFontGlyphRangesBuilder builder;
        constexpr ImWchar Ranges[] {0x0020, 0x00FF, 0x0100, 0x024F, 0x0300, 0x03FF, 0x0400, 0x052F, 0x0600, 0x06FF, 0x0E00, 0x0E7F, 0x2DE0, 0x2DFF, 0x2000, 0x206F, 0x3000, 0x30FF, 0x31F0, 0x31FF, 0xFF00, 0xFFEF, 0x4E00, 0x9FAF, 0xA640, 0xA69F, 0x3131, 0x3163, 0xAC00, 0xD7A3, 0};
        builder.AddRanges(Ranges);
        builder.AddRanges(Io->Fonts->GetGlyphRangesChineseSimplifiedCommon());
        builder.BuildRanges(&RanGes);
    }
    ImFontConfig config;
    config.FontDataOwnedByAtlas = false;
    config.SizePixels = 35;
    config.GlyphRanges = RanGes.Data;
    config.OversampleH = 1;
    config.OversampleV = 1;
    return Io->Fonts->AddFontFromFileTTF(path, 0, &config);
}
ImFont* font;