#include "File.h"

#include <tinyxml2.h>
#include <vector>
#include <cstring>

#include "WidgetBuilders.h"

using namespace tinyxml2;

namespace Skoga{
    // Storage for text strings loaded from XML files
    static std::vector<char*> g_TextCache;
    Ref<Widget> GenerateError(const char* error){
        auto errorText = CreateRef<TextWidget>(error);
        errorText->GetStyle().TextColor = Color(1.0f, 0.0f, 0.0f);
        errorText->GetStyle().FontSize = 14.0f;
        errorText->GetStyle().FontFamily = FontConsolas;
        errorText->SetHorizontalAlignment(HorizontalAlignment::Center);
        errorText->SetVerticalAlignment(VerticalAlignment::Middle);

        return Box(
            Box(errorText)
                .FlexDirection(FlexDirection::Column)
                .JustifyContent(JustifyContent::Center)
                .AlignItems(AlignItems::Center)
                .Flex()
            ).BgColor(Color(0.1f, 0.1f, 0.1f))
            .Build();
    }

    // Helper to parse color from hex string (#RRGGBB or #RRGGBBAA)
    static Color ParseColor(const char* colorStr) {
        if (!colorStr || colorStr[0] != '#') return Color(1.0f, 1.0f, 1.0f);
        
        unsigned int hex = 0;
        sscanf(colorStr + 1, "%x", &hex);
        
        int len = strlen(colorStr + 1);
        if (len == 6) {
            return Color(
                ((hex >> 16) & 0xFF) / 255.0f,
                ((hex >> 8) & 0xFF) / 255.0f,
                (hex & 0xFF) / 255.0f
            );
        } else if (len == 8) {
            return Color(
                ((hex >> 24) & 0xFF) / 255.0f,
                ((hex >> 16) & 0xFF) / 255.0f,
                ((hex >> 8) & 0xFF) / 255.0f,
                (hex & 0xFF) / 255.0f
            );
        }
        return Color(1.0f, 1.0f, 1.0f);
    }

    // Helper to parse float attribute
    static float ParseFloat(const XMLElement* element, const char* attrName, float defaultValue = 0.0f) {
        const char* value = element->Attribute(attrName);
        return value ? static_cast<float>(atof(value)) : defaultValue;
    }

    // Helper to parse boolean attribute
    static bool ParseBool(const XMLElement* element, const char* attrName, bool defaultValue = false) {
        const char* value = element->Attribute(attrName);
        if (!value) return defaultValue;
        return strcmp(value, "true") == 0 || strcmp(value, "1") == 0;
    }

    // Apply style attributes to Box
    static void ApplyBoxAttributes(Box& box, const XMLElement* element) {
        // Background color
        const char* bgColor = element->Attribute("background-color");
        if (bgColor) box.BgColor(ParseColor(bgColor));

        // Border
        const char* borderColor = element->Attribute("border-color");
        if (borderColor) box.BorderColor(ParseColor(borderColor));
        
        float borderRadius = ParseFloat(element, "border-radius");
        if (borderRadius > 0) box.BorderRadius(borderRadius);

        // Flex
        const char* flexAttr = element->Attribute("flex");
        if (flexAttr) {
            if (strcmp(flexAttr, "true") == 0) {
                box.Flex(1.0f);
            } else {
                box.Flex(static_cast<float>(atof(flexAttr)));
            }
        }

        // Flex direction
        const char* flexDir = element->Attribute("flex-direction");
        if (flexDir) {
            if (strcmp(flexDir, "row") == 0) box.FlexDirection(FlexDirection::Row);
            else if (strcmp(flexDir, "column") == 0) box.FlexDirection(FlexDirection::Column);
            else if (strcmp(flexDir, "row-reverse") == 0) box.FlexDirection(FlexDirection::RowReverse);
            else if (strcmp(flexDir, "column-reverse") == 0) box.FlexDirection(FlexDirection::ColumnReverse);
        }

        // Justify content
        const char* justify = element->Attribute("justify-content");
        if (justify) {
            if (strcmp(justify, "flex-start") == 0) box.JustifyContent(JustifyContent::FlexStart);
            else if (strcmp(justify, "center") == 0) box.JustifyContent(JustifyContent::Center);
            else if (strcmp(justify, "flex-end") == 0) box.JustifyContent(JustifyContent::FlexEnd);
            else if (strcmp(justify, "space-between") == 0) box.JustifyContent(JustifyContent::SpaceBetween);
            else if (strcmp(justify, "space-around") == 0) box.JustifyContent(JustifyContent::SpaceAround);
            else if (strcmp(justify, "space-evenly") == 0) box.JustifyContent(JustifyContent::SpaceEvenly);
        }

        // Align items
        const char* align = element->Attribute("align-items");
        if (align) {
            if (strcmp(align, "flex-start") == 0) box.AlignItems(AlignItems::FlexStart);
            else if (strcmp(align, "center") == 0) box.AlignItems(AlignItems::Center);
            else if (strcmp(align, "flex-end") == 0) box.AlignItems(AlignItems::FlexEnd);
            else if (strcmp(align, "stretch") == 0) box.AlignItems(AlignItems::Stretch);
            else if (strcmp(align, "baseline") == 0) box.AlignItems(AlignItems::Baseline);
        }

        // Padding
        const char* padding = element->Attribute("padding");
        if (padding) {
            box.Padding(static_cast<float>(atof(padding)));
        } else {
            float paddingTop = ParseFloat(element, "padding-top", -1.0f);
            float paddingRight = ParseFloat(element, "padding-right", -1.0f);
            float paddingBottom = ParseFloat(element, "padding-bottom", -1.0f);
            float paddingLeft = ParseFloat(element, "padding-left", -1.0f);
            
            if (paddingTop >= 0 || paddingRight >= 0 || paddingBottom >= 0 || paddingLeft >= 0) {
                box.Padding(
                    paddingTop >= 0 ? paddingTop : 0,
                    paddingRight >= 0 ? paddingRight : 0,
                    paddingBottom >= 0 ? paddingBottom : 0,
                    paddingLeft >= 0 ? paddingLeft : 0
                );
            }
        }

        // Margin
        const char* margin = element->Attribute("margin");
        if (margin) {
            box.Margin(static_cast<float>(atof(margin)));
        } else {
            float marginTop = ParseFloat(element, "margin-top", -1.0f);
            float marginRight = ParseFloat(element, "margin-right", -1.0f);
            float marginBottom = ParseFloat(element, "margin-bottom", -1.0f);
            float marginLeft = ParseFloat(element, "margin-left", -1.0f);
            
            if (marginTop >= 0 || marginRight >= 0 || marginBottom >= 0 || marginLeft >= 0) {
                box.Margin(
                    marginTop >= 0 ? marginTop : 0,
                    marginRight >= 0 ? marginRight : 0,
                    marginBottom >= 0 ? marginBottom : 0,
                    marginLeft >= 0 ? marginLeft : 0
                );
            }
        }

        // Width and Height
        float width = ParseFloat(element, "width");
        if (width > 0) box.Width(width);
        
        float height = ParseFloat(element, "height");
        if (height > 0) box.Height(height);
    }

    // Forward declaration
    static Ref<Widget> ParseElement(const XMLElement* element);

    // Parse box element
    static Ref<Widget> ParseBox(const XMLElement* element) {
        Box box;
        ApplyBoxAttributes(box, element);

        // Parse children
        for (const XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement()) {
            auto childWidget = ParseElement(child);
            if (childWidget) {
                box.Add(childWidget);
            }
        }

        return box.Build();
    }

    // Parse text element
    static Ref<Widget> ParseText(const XMLElement* element) {
        const char* textContent = element->GetText();
        if (!textContent) textContent = "";

        // Create a persistent copy of the text
        char* textCopy = _strdup(textContent);
        g_TextCache.push_back(textCopy);

        Text text(textCopy);

        // Alignment
        const char* hAlign = element->Attribute("horizontal-align");
        if (hAlign) {
            if (strcmp(hAlign, "left") == 0) text.HAlign(HorizontalAlignment::Left);
            else if (strcmp(hAlign, "center") == 0) text.HAlign(HorizontalAlignment::Center);
            else if (strcmp(hAlign, "right") == 0) text.HAlign(HorizontalAlignment::Right);
        }

        const char* vAlign = element->Attribute("vertical-align");
        if (vAlign) {
            if (strcmp(vAlign, "top") == 0) text.VAlign(VerticalAlignment::Top);
            else if (strcmp(vAlign, "middle") == 0) text.VAlign(VerticalAlignment::Middle);
            else if (strcmp(vAlign, "bottom") == 0) text.VAlign(VerticalAlignment::Bottom);
        }

        auto textWidget = text.Build();
        
        // Text color
        const char* textColor = element->Attribute("color");
        if (textColor) {
            textWidget->GetStyle().TextColor = ParseColor(textColor);
        }

        return textWidget;
    }

    // Parse button element
    static Ref<Widget> ParseButton(const XMLElement* element) {
        Button button;

        // Parse children
        for (const XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement()) {
            auto childWidget = ParseElement(child);
            if (childWidget) {
                button.Add(childWidget);
            }
        }

        return button.Build();
    }

    // Parse any element
    static Ref<Widget> ParseElement(const XMLElement* element) {
        if (!element) return nullptr;

        const char* name = element->Name();
        
        if (strcmp(name, "box") == 0) {
            return ParseBox(element);
        } else if (strcmp(name, "text") == 0) {
            return ParseText(element);
        } else if (strcmp(name, "button") == 0) {
            return ParseButton(element);
        }

        return nullptr;
    }

    Ref<Widget> LoadFromFile(const char* filepath){
        XMLDocument doc;
        if (doc.LoadFile(filepath) != XML_SUCCESS){
            return GenerateError("Failed to load layout file.");
        }

        XMLElement* root = doc.RootElement();
        if (!root) {
            return GenerateError("No root element found in layout file.");
        }

        auto widget = ParseElement(root);
        if (!widget) {
            return GenerateError("Failed to parse root element.");
        }

        return widget;
    }
}