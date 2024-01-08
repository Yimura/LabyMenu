#pragma once
#include "../base/String.hpp"
#include "../UnityEngine/Color.hpp"
#include "../UnityEngine/Color32.hpp"
#include "../UnityEngine/MaskableGraphic.hpp"
#include "../UnityEngine/Matrix4x4.hpp"
#include "../UnityEngine/Vector2.hpp"
#include "Extents.hpp"
#include "HighlightState.hpp"
#include "TMP_ColorGradient.hpp"
#include "TMP_FontStyleStack.hpp"
#include "TMP_TextProcessingStack.hpp"
#include "TMP_Text_SpecialCharacter.hpp"
#include "TMP_Text_TextBackingContainer.hpp"
#include "VertexGradient.hpp"

#include <cstdint>

namespace YimMenu
{
	class TMP_Text_Fields : public UnityEngine_UI_MaskableGraphic_Fields
	{
	public:
		String* m_text;
		bool m_IsTextBackingStringDirty;
		struct TMPro_ITextPreprocessor_o* m_TextPreprocessor;
		bool m_isRightToLeft;
		struct TMPro_TMP_FontAsset_o* m_fontAsset;
		struct TMPro_TMP_FontAsset_o* m_currentFontAsset;
		bool m_isSDFShader;
		struct UnityEngine_Material_o* m_sharedMaterial;
		struct UnityEngine_Material_o* m_currentMaterial;
		int32_t m_currentMaterialIndex;
		struct UnityEngine_Material_array* m_fontSharedMaterials;
		struct UnityEngine_Material_o* m_fontMaterial;
		struct UnityEngine_Material_array* m_fontMaterials;
		bool m_isMaterialDirty;
		Color32 m_fontColor32;
		Color m_fontColor;
		Color32 m_underlineColor;
		Color32 m_strikethroughColor;
		bool m_enableVertexGradient;
		int32_t m_colorMode;
		VertexGradient m_fontColorGradient;
		TMP_ColorGradient_o* m_fontColorGradientPreset;
		struct TMPro_TMP_SpriteAsset_o* m_spriteAsset;
		bool m_tintAllSprites;
		bool m_tintSprite;
		Color32 m_spriteColor;
		struct TMPro_TMP_StyleSheet_o* m_StyleSheet;
		struct TMPro_TMP_Style_o* m_TextStyle;
		int32_t m_TextStyleHashCode;
		bool m_overrideHtmlColors;
		Color32 m_faceColor;
		Color32 m_outlineColor;
		float m_outlineWidth;
		float m_fontSize;
		float m_currentFontSize;
		float m_fontSizeBase;
		TMP_TextProcessingStack<float> m_sizeStack;
		int32_t m_fontWeight;
		int32_t m_FontWeightInternal;
		TMP_TextProcessingStack<int32_t> m_FontWeightStack;
		bool m_enableAutoSizing;
		float m_maxFontSize;
		float m_minFontSize;
		int32_t m_AutoSizeIterationCount;
		int32_t m_AutoSizeMaxIterationCount;
		bool m_IsAutoSizePointSizeSet;
		float m_fontSizeMin;
		float m_fontSizeMax;
		int32_t m_fontStyle;
		int32_t m_FontStyleInternal;
		TMP_FontStyleStack m_fontStyleStack;
		bool m_isUsingBold;
		int32_t m_HorizontalAlignment;
		int32_t m_VerticalAlignment;
		int32_t m_textAlignment;
		int32_t m_lineJustification;
		TMP_TextProcessingStack<int32_t> m_lineJustificationStack;
		struct UnityEngine_Vector3_array* m_textContainerLocalCorners;
		float m_characterSpacing;
		float m_cSpacing;
		float m_monoSpacing;
		float m_wordSpacing;
		float m_lineSpacing;
		float m_lineSpacingDelta;
		float m_lineHeight;
		bool m_IsDrivenLineSpacing;
		float m_lineSpacingMax;
		float m_paragraphSpacing;
		float m_charWidthMaxAdj;
		float m_charWidthAdjDelta;
		bool m_enableWordWrapping;
		bool m_isCharacterWrappingEnabled;
		bool m_isNonBreakingSpace;
		bool m_isIgnoringAlignment;
		float m_wordWrappingRatios;
		int32_t m_overflowMode;
		int32_t m_firstOverflowCharacterIndex;
		struct TMPro_TMP_Text_o* m_linkedTextComponent;
		struct TMPro_TMP_Text_o* parentLinkedComponent;
		bool m_isTextTruncated;
		bool m_enableKerning;
		float m_GlyphHorizontalAdvanceAdjustment;
		bool m_enableExtraPadding;
		bool checkPaddingRequired;
		bool m_isRichText;
		bool m_parseCtrlCharacters;
		bool m_isOverlay;
		bool m_isOrthographic;
		bool m_isCullingEnabled;
		bool m_isMaskingEnabled;
		bool isMaskUpdateRequired;
		bool m_ignoreCulling;
		int32_t m_horizontalMapping;
		int32_t m_verticalMapping;
		float m_uvLineOffset;
		int32_t m_renderMode;
		int32_t m_geometrySortingOrder;
		bool m_IsTextObjectScaleStatic;
		bool m_VertexBufferAutoSizeReduction;
		int32_t m_firstVisibleCharacter;
		int32_t m_maxVisibleCharacters;
		int32_t m_maxVisibleWords;
		int32_t m_maxVisibleLines;
		bool m_useMaxVisibleDescender;
		int32_t m_pageToDisplay;
		bool m_isNewPage;
		Vector4 m_margin;
		float m_marginLeft;
		float m_marginRight;
		float m_marginWidth;
		float m_marginHeight;
		float m_width;
		struct TMPro_TMP_TextInfo_o* m_textInfo;
		bool m_havePropertiesChanged;
		bool m_isUsingLegacyAnimationComponent;
		struct UnityEngine_Transform_o* m_transform;
		struct UnityEngine_RectTransform_o* m_rectTransform;
		Vector2 m_PreviousRectTransformSize;
		Vector2 m_PreviousPivotPosition;
		bool _autoSizeTextContainer_k__BackingField;
		bool m_autoSizeTextContainer;
		struct UnityEngine_Mesh_o* m_mesh;
		bool m_isVolumetricText;
		struct System_Action_TMP_TextInfo__o* OnPreRenderText;
		struct TMPro_TMP_SpriteAnimator_o* m_spriteAnimator;
		float m_flexibleHeight;
		float m_flexibleWidth;
		float m_minWidth;
		float m_minHeight;
		float m_maxWidth;
		float m_maxHeight;
		struct UnityEngine_UI_LayoutElement_o* m_LayoutElement;
		float m_preferredWidth;
		float m_renderedWidth;
		bool m_isPreferredWidthDirty;
		float m_preferredHeight;
		float m_renderedHeight;
		bool m_isPreferredHeightDirty;
		bool m_isCalculatingPreferredValues;
		int32_t m_layoutPriority;
		bool m_isLayoutDirty;
		bool m_isAwake;
		bool m_isWaitingOnResourceLoad;
		int32_t m_inputSource;
		float m_fontScaleMultiplier;
		float tag_LineIndent;
		float tag_Indent;
		TMP_TextProcessingStack<float> m_indentStack;
		bool tag_NoParsing;
		bool m_isParsingText;
		Matrix4x4 m_FXMatrix;
		bool m_isFXMatrixSet;
		struct TMPro_TMP_Text_UnicodeChar_array* m_TextProcessingArray;
		int32_t m_InternalTextProcessingArraySize;
		struct TMPro_TMP_CharacterInfo_array* m_internalCharacterInfo;
		int32_t m_totalCharacterCount;
		int32_t m_characterCount;
		int32_t m_firstCharacterOfLine;
		int32_t m_firstVisibleCharacterOfLine;
		int32_t m_lastCharacterOfLine;
		int32_t m_lastVisibleCharacterOfLine;
		int32_t m_lineNumber;
		int32_t m_lineVisibleCharacterCount;
		int32_t m_pageNumber;
		float m_PageAscender;
		float m_maxTextAscender;
		float m_maxCapHeight;
		float m_ElementAscender;
		float m_ElementDescender;
		float m_maxLineAscender;
		float m_maxLineDescender;
		float m_startOfLineAscender;
		float m_startOfLineDescender;
		float m_lineOffset;
		Extents m_meshExtents;
		Color32 m_htmlColor;
		TMP_TextProcessingStack<Color32> m_colorStack;
		TMP_TextProcessingStack<Color32> m_underlineColorStack;
		TMP_TextProcessingStack<Color32> m_strikethroughColorStack;
		TMP_TextProcessingStack<HighlightState> m_HighlightStateStack;
		TMP_ColorGradient_o* m_colorGradientPreset;
		TMP_TextProcessingStack<TMP_ColorGradient_o*> m_colorGradientStack;
		bool m_colorGradientPresetIsTinted;
		float m_tabSpacing;
		float m_spacing;
		struct TMPro_TMP_TextProcessingStack_int__array* m_TextStyleStacks;
		int32_t m_TextStyleStackDepth;
		TMP_TextProcessingStack<int> m_ItalicAngleStack;
		int32_t m_ItalicAngle;
		TMP_TextProcessingStack<int> m_actionStack;
		float m_padding;
		float m_baselineOffset;
		TMP_TextProcessingStack<float> m_baselineOffsetStack;
		float m_xAdvance;
		int32_t m_textElementType;
		struct TMPro_TMP_TextElement_o* m_cached_TextElement;
		TMP_Text_SpecialCharacter m_Ellipsis;
		TMP_Text_SpecialCharacter m_Underline;
		struct TMPro_TMP_SpriteAsset_o* m_defaultSpriteAsset;
		struct TMPro_TMP_SpriteAsset_o* m_currentSpriteAsset;
		int32_t m_spriteCount;
		int32_t m_spriteIndex;
		int32_t m_spriteAnimationID;
		bool m_ignoreActiveState;
		TMP_Text_TextBackingContainer m_TextBackingArray;
		struct System_Decimal_array* k_Power;
	};
	static_assert(sizeof(TMP_Text_Fields) == 0x6E0);

	struct TMP_Text_o
	{
		void* klass;
		void* monitor;
		TMP_Text_Fields fields;
	};
}
