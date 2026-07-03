#ifndef IMAGETRIPLET_H
#define IMAGETRIPLET_H

class GolImage;

// One multi-state image record: three images per widget state. Shared by
// MenuStyleTable::MultiStateStyle and MenuInputBindingTable::MultiStateBinding,
// which parse the same on-disk layout.
// SIZE 0x0c
class ImageTriplet {
public:
	GolImage* m_unk0x00; // 0x00
	GolImage* m_unk0x04; // 0x04
	GolImage* m_unk0x08; // 0x08
};

#endif // IMAGETRIPLET_H
