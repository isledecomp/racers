#ifndef MENUBINDINGTOKEN_H
#define MENUBINDINGTOKEN_H

// Block-type tokens in the .MIB/.MID menu binding format, dispatched by
// MenuInputBindingTable::ParseSection. Each block id corresponds to one widget
// kind (see the matching MenuInputBindingTable::Parse*Bindings method and the
// widget it builds). Grounded in decoded LEGO.JAM .MIB item types.
enum MenuBindingToken {
	c_blockRegion = 0x37,        // plain MenuWidget region
	c_blockImage = 0x38,         // MenuImage
	c_blockTextLabel = 0x39,     // MenuTextLabel
	c_blockFrame = 0x3a,         // MenuFrame (nine-slice border)
	c_blockButton = 0x3b,        // MenuButton (multi-state icon)
	c_blockMultiState = 0x3c,    // multi-state font+image binding
	c_blockHotspot = 0x3d,       // MenuHotspotButton
	c_blockSelector = 0x3e,      // MenuSelector (banner)
	c_blockModelCarousel = 0x3f, // MenuModelCarousel
	c_blockComposite = 0x40,     // composite (OptionsRow)
	c_blockScene = 0x42,         // MenuSceneView (3D scene)
	c_blockTextField = 0x43,     // MenuTextField (editable text)
	c_blockSceneRef = 0x45,      // simple scene reference
};

// Shared field tokens inside .MSB style bodies (several ids are
// style-scoped; those stay with their style structs).
enum MenuStyleFieldToken {
	c_styleImage = 0x28,
	c_styleFont = 0x29,
	c_styleColors = 0x2a,
	c_styleSounds = 0x2b,
	c_resourceHeader = 0x27,
	c_styleIcon = 0x3a,
	c_styleBlockImage = 0x32,
	c_styleBlockText = 0x33,
	c_styleBlockFrame = 0x34,
	c_styleBlockButton = 0x35,
	c_styleBlockMultiState = 0x36,
	c_styleBlockHotspot = 0x37,
	c_styleBlockCarousel = 0x38,
	c_styleBlockSelector = 0x39,
	c_styleBlockComposite = 0x3b,
	c_styleBlockTextButton = 0x3e,
};

#endif // MENUBINDINGTOKEN_H
