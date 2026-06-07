#ifndef MENUBINDINGTOKEN_H
#define MENUBINDINGTOKEN_H

// Block-type tokens in the .MIB/.MID menu binding format, dispatched by
// MenuInputBindingTable::VTable0x14. Each block id corresponds to one widget
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

#endif // MENUBINDINGTOKEN_H
