#include "audio/soundgroupbinding.h"
#include "camera/golcamera.h"
#include "core/gol.h"
#include "decomp.h"
#include "golerror.h"
#include "golscenenode.h"
#include "menu/menugamecontext.h"
#include "menu/screens/carmodelscreenbase.h"
#include "mesh/golmodelbase.h"
#include "racer/drivercosmetics.h"

#include <float.h>
#include <math.h>
#include <string.h>

extern const LegoFloat g_violetShoalTwo;
extern const LegoFloat g_carBuildModelHeightScale;

DECOMP_SIZE_ASSERT(CarModelScreenBase::CarPartPlacement, 0x2d0)
DECOMP_SIZE_ASSERT(CarModelScreenBase::CarPartPlacement::CreateParams, 0x30)

// GLOBAL: LEGORACERS 0x004b2e68
LegoFloat g_unk0x4b2e68 = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b2e80
const LegoFloat g_carPartCameraPositions[] = {
	0.0f, -14.0f, 9.0f,  0.0f, -10.0f, 14.0f, 0.0f, -0.3f, 17.0f, 0.0f,
	0.0f, -18.0f, 10.0f, 0.0f, -12.0f, 17.0f, 0.0f, -0.3f, 20.0f,
};

// GLOBAL: LEGORACERS 0x004b2ed4
extern const LegoFloat g_carPartHoverHeight = 1.2f;

// GLOBAL: LEGORACERS 0x004b2ed8
LegoFloat g_unk0x4b2ed8 = 1.0f;

// GLOBAL: LEGORACERS 0x004c7668
LegoFloat g_fieldAt0x2308AngleStep = 0.0f;

// GLOBAL: LEGORACERS 0x004b02f4
extern const LegoFloat g_negativeRadiansToTableIndex = -162.97466f;

// GLOBAL: LEGORACERS 0x004b0428
extern const LegoFloat g_halfPi = 1.5707964f;

// GLOBAL: LEGORACERS 0x004bf7ec
LegoFloat g_cosineTable[1024] = {
	1.0f,           0.999981165f,   0.999924719f,   0.999830604f,   0.999698818f,   0.999529421f,
	0.999322414f,   0.999077737f,   0.99879545f,    0.998475552f,   0.998118103f,   0.997723043f,
	0.997290432f,   0.996820271f,   0.996312618f,   0.995767415f,   0.99518472f,    0.994564593f,
	0.993906975f,   0.993211925f,   0.992479563f,   0.991709769f,   0.990902662f,   0.990058184f,
	0.989176512f,   0.988257587f,   0.987301409f,   0.986308098f,   0.985277653f,   0.984210074f,
	0.983105481f,   0.981963873f,   0.980785251f,   0.979569793f,   0.97831738f,    0.977028131f,
	0.975702107f,   0.974339366f,   0.972939968f,   0.971503913f,   0.970031261f,   0.968522072f,
	0.966976464f,   0.965394437f,   0.963776052f,   0.962121427f,   0.960430503f,   0.958703458f,
	0.956940353f,   0.955141187f,   0.953306019f,   0.95143503f,    0.949528158f,   0.947585583f,
	0.945607305f,   0.943593442f,   0.941544056f,   0.939459205f,   0.937339008f,   0.935183525f,
	0.932992816f,   0.93076694f,    0.928506076f,   0.926210225f,   0.923879504f,   0.921514034f,
	0.919113874f,   0.916679084f,   0.914209783f,   0.91170603f,    0.909168005f,   0.906595707f,
	0.903989315f,   0.901348829f,   0.898674488f,   0.895966232f,   0.893224299f,   0.890448749f,
	0.887639642f,   0.884797096f,   0.881921291f,   0.879012227f,   0.876070082f,   0.873094976f,
	0.870086968f,   0.867046237f,   0.863972843f,   0.860866964f,   0.857728601f,   0.854557991f,
	0.851355195f,   0.848120332f,   0.84485358f,    0.841554999f,   0.838224709f,   0.834862888f,
	0.831469595f,   0.82804507f,    0.824589312f,   0.8211025f,     0.817584813f,   0.81403631f,
	0.81045717f,    0.806847572f,   0.803207517f,   0.799537241f,   0.795836926f,   0.792106569f,
	0.78834641f,    0.784556568f,   0.780737221f,   0.77688849f,    0.773010433f,   0.769103348f,
	0.765167236f,   0.761202395f,   0.757208824f,   0.753186822f,   0.749136388f,   0.745057762f,
	0.740951121f,   0.736816585f,   0.732654274f,   0.728464365f,   0.724247098f,   0.720002532f,
	0.715730846f,   0.711432219f,   0.707106769f,   0.702754736f,   0.698376238f,   0.693971455f,
	0.689540565f,   0.685083687f,   0.680601001f,   0.676092684f,   0.671558976f,   0.666999936f,
	0.662415802f,   0.657806695f,   0.653172851f,   0.64851439f,    0.643831551f,   0.639124453f,
	0.634393275f,   0.629638255f,   0.624859512f,   0.620057225f,   0.615231574f,   0.610382795f,
	0.605511069f,   0.600616455f,   0.59569931f,    0.590759695f,   0.585797846f,   0.580813944f,
	0.575808167f,   0.570780754f,   0.565731823f,   0.560661554f,   0.555570245f,   0.550457954f,
	0.545324981f,   0.540171444f,   0.534997642f,   0.529803634f,   0.524589658f,   0.519356012f,
	0.514102757f,   0.50883013f,    0.50353837f,    0.498227656f,   0.492898196f,   0.487550169f,
	0.482183784f,   0.47679922f,    0.471396744f,   0.465976506f,   0.460538715f,   0.455083579f,
	0.449611336f,   0.444122136f,   0.438616246f,   0.433093816f,   0.427555084f,   0.422000259f,
	0.416429549f,   0.410843164f,   0.405241311f,   0.399624199f,   0.393992037f,   0.388345033f,
	0.382683426f,   0.377007425f,   0.371317208f,   0.365612984f,   0.359895051f,   0.354163527f,
	0.348418683f,   0.342660725f,   0.336889863f,   0.331106305f,   0.32531029f,    0.319502026f,
	0.313681751f,   0.307849646f,   0.302005947f,   0.296150893f,   0.290284663f,   0.284407526f,
	0.27851969f,    0.272621363f,   0.266712755f,   0.260794103f,   0.254865646f,   0.248927608f,
	0.242980182f,   0.237023607f,   0.231058106f,   0.225083917f,   0.219101235f,   0.213110313f,
	0.207111374f,   0.201104641f,   0.195090324f,   0.18906866f,    0.183039889f,   0.177004218f,
	0.170961887f,   0.164913118f,   0.15885815f,    0.152797192f,   0.146730468f,   0.140658244f,
	0.134580702f,   0.128498107f,   0.122410677f,   0.116318628f,   0.110222206f,   0.104121633f,
	0.0980171412f,  0.0919089541f,  0.0857973099f,  0.0796824396f,  0.0735645667f,  0.0674439222f,
	0.061320737f,   0.0551952422f,  0.0490676723f,  0.0429382585f,  0.0368072242f,  0.0306748021f,
	0.024541229f,   0.0184067301f,  0.0122715384f,  0.00613588514f, 0.0f,           -0.00613588514f,
	-0.0122715384f, -0.0184067301f, -0.024541229f,  -0.0306748021f, -0.0368072242f, -0.0429382585f,
	-0.0490676723f, -0.0551952422f, -0.061320737f,  -0.0674439222f, -0.0735645667f, -0.0796824396f,
	-0.0857973099f, -0.0919089541f, -0.0980171412f, -0.104121633f,  -0.110222206f,  -0.116318628f,
	-0.122410677f,  -0.128498107f,  -0.134580702f,  -0.140658244f,  -0.146730468f,  -0.152797192f,
	-0.15885815f,   -0.164913118f,  -0.170961887f,  -0.177004218f,  -0.183039889f,  -0.18906866f,
	-0.195090324f,  -0.201104641f,  -0.207111374f,  -0.213110313f,  -0.219101235f,  -0.225083917f,
	-0.231058106f,  -0.237023607f,  -0.242980182f,  -0.248927608f,  -0.254865646f,  -0.260794103f,
	-0.266712755f,  -0.272621363f,  -0.27851969f,   -0.284407526f,  -0.290284663f,  -0.296150893f,
	-0.302005947f,  -0.307849646f,  -0.313681751f,  -0.319502026f,  -0.32531029f,   -0.331106305f,
	-0.336889863f,  -0.342660725f,  -0.348418683f,  -0.354163527f,  -0.359895051f,  -0.365612984f,
	-0.371317208f,  -0.377007425f,  -0.382683426f,  -0.388345033f,  -0.393992037f,  -0.399624199f,
	-0.405241311f,  -0.410843164f,  -0.416429549f,  -0.422000259f,  -0.427555084f,  -0.433093816f,
	-0.438616246f,  -0.444122136f,  -0.449611336f,  -0.455083579f,  -0.460538715f,  -0.465976506f,
	-0.471396744f,  -0.47679922f,   -0.482183784f,  -0.487550169f,  -0.492898196f,  -0.498227656f,
	-0.50353837f,   -0.50883013f,   -0.514102757f,  -0.519356012f,  -0.524589658f,  -0.529803634f,
	-0.534997642f,  -0.540171444f,  -0.545324981f,  -0.550457954f,  -0.555570245f,  -0.560661554f,
	-0.565731823f,  -0.570780754f,  -0.575808167f,  -0.580813944f,  -0.585797846f,  -0.590759695f,
	-0.59569931f,   -0.600616455f,  -0.605511069f,  -0.610382795f,  -0.615231574f,  -0.620057225f,
	-0.624859512f,  -0.629638255f,  -0.634393275f,  -0.639124453f,  -0.643831551f,  -0.64851439f,
	-0.653172851f,  -0.657806695f,  -0.662415802f,  -0.666999936f,  -0.671558976f,  -0.676092684f,
	-0.680601001f,  -0.685083687f,  -0.689540565f,  -0.693971455f,  -0.698376238f,  -0.702754736f,
	-0.707106769f,  -0.711432219f,  -0.715730846f,  -0.720002532f,  -0.724247098f,  -0.728464365f,
	-0.732654274f,  -0.736816585f,  -0.740951121f,  -0.745057762f,  -0.749136388f,  -0.753186822f,
	-0.757208824f,  -0.761202395f,  -0.765167236f,  -0.769103348f,  -0.773010433f,  -0.77688849f,
	-0.780737221f,  -0.784556568f,  -0.78834641f,   -0.792106569f,  -0.795836926f,  -0.799537241f,
	-0.803207517f,  -0.806847572f,  -0.81045717f,   -0.81403631f,   -0.817584813f,  -0.8211025f,
	-0.824589312f,  -0.82804507f,   -0.831469595f,  -0.834862888f,  -0.838224709f,  -0.841554999f,
	-0.84485358f,   -0.848120332f,  -0.851355195f,  -0.854557991f,  -0.857728601f,  -0.860866964f,
	-0.863972843f,  -0.867046237f,  -0.870086968f,  -0.873094976f,  -0.876070082f,  -0.879012227f,
	-0.881921291f,  -0.884797096f,  -0.887639642f,  -0.890448749f,  -0.893224299f,  -0.895966232f,
	-0.898674488f,  -0.901348829f,  -0.903989315f,  -0.906595707f,  -0.909168005f,  -0.91170603f,
	-0.914209783f,  -0.916679084f,  -0.919113874f,  -0.921514034f,  -0.923879504f,  -0.926210225f,
	-0.928506076f,  -0.93076694f,   -0.932992816f,  -0.935183525f,  -0.937339008f,  -0.939459205f,
	-0.941544056f,  -0.943593442f,  -0.945607305f,  -0.947585583f,  -0.949528158f,  -0.95143503f,
	-0.953306019f,  -0.955141187f,  -0.956940353f,  -0.958703458f,  -0.960430503f,  -0.962121427f,
	-0.963776052f,  -0.965394437f,  -0.966976464f,  -0.968522072f,  -0.970031261f,  -0.971503913f,
	-0.972939968f,  -0.974339366f,  -0.975702107f,  -0.977028131f,  -0.97831738f,   -0.979569793f,
	-0.980785251f,  -0.981963873f,  -0.983105481f,  -0.984210074f,  -0.985277653f,  -0.986308098f,
	-0.987301409f,  -0.988257587f,  -0.989176512f,  -0.990058184f,  -0.990902662f,  -0.991709769f,
	-0.992479563f,  -0.993211925f,  -0.993906975f,  -0.994564593f,  -0.99518472f,   -0.995767415f,
	-0.996312618f,  -0.996820271f,  -0.997290432f,  -0.997723043f,  -0.998118103f,  -0.998475552f,
	-0.99879545f,   -0.999077737f,  -0.999322414f,  -0.999529421f,  -0.999698818f,  -0.999830604f,
	-0.999924719f,  -0.999981165f,  -1.0f,          -0.999981165f,  -0.999924719f,  -0.999830604f,
	-0.999698818f,  -0.999529421f,  -0.999322414f,  -0.999077737f,  -0.99879545f,   -0.998475552f,
	-0.998118103f,  -0.997723043f,  -0.997290432f,  -0.996820271f,  -0.996312618f,  -0.995767415f,
	-0.99518472f,   -0.994564593f,  -0.993906975f,  -0.993211925f,  -0.992479563f,  -0.991709769f,
	-0.990902662f,  -0.990058184f,  -0.989176512f,  -0.988257587f,  -0.987301409f,  -0.986308098f,
	-0.985277653f,  -0.984210074f,  -0.983105481f,  -0.981963873f,  -0.980785251f,  -0.979569793f,
	-0.97831738f,   -0.977028131f,  -0.975702107f,  -0.974339366f,  -0.972939968f,  -0.971503913f,
	-0.970031261f,  -0.968522072f,  -0.966976464f,  -0.965394437f,  -0.963776052f,  -0.962121427f,
	-0.960430503f,  -0.958703458f,  -0.956940353f,  -0.955141187f,  -0.953306019f,  -0.95143503f,
	-0.949528158f,  -0.947585583f,  -0.945607305f,  -0.943593442f,  -0.941544056f,  -0.939459205f,
	-0.937339008f,  -0.935183525f,  -0.932992816f,  -0.93076694f,   -0.928506076f,  -0.926210225f,
	-0.923879504f,  -0.921514034f,  -0.919113874f,  -0.916679084f,  -0.914209783f,  -0.91170603f,
	-0.909168005f,  -0.906595707f,  -0.903989315f,  -0.901348829f,  -0.898674488f,  -0.895966232f,
	-0.893224299f,  -0.890448749f,  -0.887639642f,  -0.884797096f,  -0.881921291f,  -0.879012227f,
	-0.876070082f,  -0.873094976f,  -0.870086968f,  -0.867046237f,  -0.863972843f,  -0.860866964f,
	-0.857728601f,  -0.854557991f,  -0.851355195f,  -0.848120332f,  -0.84485358f,   -0.841554999f,
	-0.838224709f,  -0.834862888f,  -0.831469595f,  -0.82804507f,   -0.824589312f,  -0.8211025f,
	-0.817584813f,  -0.81403631f,   -0.81045717f,   -0.806847572f,  -0.803207517f,  -0.799537241f,
	-0.795836926f,  -0.792106569f,  -0.78834641f,   -0.784556568f,  -0.780737221f,  -0.77688849f,
	-0.773010433f,  -0.769103348f,  -0.765167236f,  -0.761202395f,  -0.757208824f,  -0.753186822f,
	-0.749136388f,  -0.745057762f,  -0.740951121f,  -0.736816585f,  -0.732654274f,  -0.728464365f,
	-0.724247098f,  -0.720002532f,  -0.715730846f,  -0.711432219f,  -0.707106769f,  -0.702754736f,
	-0.698376238f,  -0.693971455f,  -0.689540565f,  -0.685083687f,  -0.680601001f,  -0.676092684f,
	-0.671558976f,  -0.666999936f,  -0.662415802f,  -0.657806695f,  -0.653172851f,  -0.64851439f,
	-0.643831551f,  -0.639124453f,  -0.634393275f,  -0.629638255f,  -0.624859512f,  -0.620057225f,
	-0.615231574f,  -0.610382795f,  -0.605511069f,  -0.600616455f,  -0.59569931f,   -0.590759695f,
	-0.585797846f,  -0.580813944f,  -0.575808167f,  -0.570780754f,  -0.565731823f,  -0.560661554f,
	-0.555570245f,  -0.550457954f,  -0.545324981f,  -0.540171444f,  -0.534997642f,  -0.529803634f,
	-0.524589658f,  -0.519356012f,  -0.514102757f,  -0.50883013f,   -0.50353837f,   -0.498227656f,
	-0.492898196f,  -0.487550169f,  -0.482183784f,  -0.47679922f,   -0.471396744f,  -0.465976506f,
	-0.460538715f,  -0.455083579f,  -0.449611336f,  -0.444122136f,  -0.438616246f,  -0.433093816f,
	-0.427555084f,  -0.422000259f,  -0.416429549f,  -0.410843164f,  -0.405241311f,  -0.399624199f,
	-0.393992037f,  -0.388345033f,  -0.382683426f,  -0.377007425f,  -0.371317208f,  -0.365612984f,
	-0.359895051f,  -0.354163527f,  -0.348418683f,  -0.342660725f,  -0.336889863f,  -0.331106305f,
	-0.32531029f,   -0.319502026f,  -0.313681751f,  -0.307849646f,  -0.302005947f,  -0.296150893f,
	-0.290284663f,  -0.284407526f,  -0.27851969f,   -0.272621363f,  -0.266712755f,  -0.260794103f,
	-0.254865646f,  -0.248927608f,  -0.242980182f,  -0.237023607f,  -0.231058106f,  -0.225083917f,
	-0.219101235f,  -0.213110313f,  -0.207111374f,  -0.201104641f,  -0.195090324f,  -0.18906866f,
	-0.183039889f,  -0.177004218f,  -0.170961887f,  -0.164913118f,  -0.15885815f,   -0.152797192f,
	-0.146730468f,  -0.140658244f,  -0.134580702f,  -0.128498107f,  -0.122410677f,  -0.116318628f,
	-0.110222206f,  -0.104121633f,  -0.0980171412f, -0.0919089541f, -0.0857973099f, -0.0796824396f,
	-0.0735645667f, -0.0674439222f, -0.061320737f,  -0.0551952422f, -0.0490676723f, -0.0429382585f,
	-0.0368072242f, -0.0306748021f, -0.024541229f,  -0.0184067301f, -0.0122715384f, -0.00613588514f,
	0.0f,           0.00613588514f, 0.0122715384f,  0.0184067301f,  0.024541229f,   0.0306748021f,
	0.0368072242f,  0.0429382585f,  0.0490676723f,  0.0551952422f,  0.061320737f,   0.0674439222f,
	0.0735645667f,  0.0796824396f,  0.0857973099f,  0.0919089541f,  0.0980171412f,  0.104121633f,
	0.110222206f,   0.116318628f,   0.122410677f,   0.128498107f,   0.134580702f,   0.140658244f,
	0.146730468f,   0.152797192f,   0.15885815f,    0.164913118f,   0.170961887f,   0.177004218f,
	0.183039889f,   0.18906866f,    0.195090324f,   0.201104641f,   0.207111374f,   0.213110313f,
	0.219101235f,   0.225083917f,   0.231058106f,   0.237023607f,   0.242980182f,   0.248927608f,
	0.254865646f,   0.260794103f,   0.266712755f,   0.272621363f,   0.27851969f,    0.284407526f,
	0.290284663f,   0.296150893f,   0.302005947f,   0.307849646f,   0.313681751f,   0.319502026f,
	0.32531029f,    0.331106305f,   0.336889863f,   0.342660725f,   0.348418683f,   0.354163527f,
	0.359895051f,   0.365612984f,   0.371317208f,   0.377007425f,   0.382683426f,   0.388345033f,
	0.393992037f,   0.399624199f,   0.405241311f,   0.410843164f,   0.416429549f,   0.422000259f,
	0.427555084f,   0.433093816f,   0.438616246f,   0.444122136f,   0.449611336f,   0.455083579f,
	0.460538715f,   0.465976506f,   0.471396744f,   0.47679922f,    0.482183784f,   0.487550169f,
	0.492898196f,   0.498227656f,   0.50353837f,    0.50883013f,    0.514102757f,   0.519356012f,
	0.524589658f,   0.529803634f,   0.534997642f,   0.540171444f,   0.545324981f,   0.550457954f,
	0.555570245f,   0.560661554f,   0.565731823f,   0.570780754f,   0.575808167f,   0.580813944f,
	0.585797846f,   0.590759695f,   0.59569931f,    0.600616455f,   0.605511069f,   0.610382795f,
	0.615231574f,   0.620057225f,   0.624859512f,   0.629638255f,   0.634393275f,   0.639124453f,
	0.643831551f,   0.64851439f,    0.653172851f,   0.657806695f,   0.662415802f,   0.666999936f,
	0.671558976f,   0.676092684f,   0.680601001f,   0.685083687f,   0.689540565f,   0.693971455f,
	0.698376238f,   0.702754736f,   0.707106769f,   0.711432219f,   0.715730846f,   0.720002532f,
	0.724247098f,   0.728464365f,   0.732654274f,   0.736816585f,   0.740951121f,   0.745057762f,
	0.749136388f,   0.753186822f,   0.757208824f,   0.761202395f,   0.765167236f,   0.769103348f,
	0.773010433f,   0.77688849f,    0.780737221f,   0.784556568f,   0.78834641f,    0.792106569f,
	0.795836926f,   0.799537241f,   0.803207517f,   0.806847572f,   0.81045717f,    0.81403631f,
	0.817584813f,   0.8211025f,     0.824589312f,   0.82804507f,    0.831469595f,   0.834862888f,
	0.838224709f,   0.841554999f,   0.84485358f,    0.848120332f,   0.851355195f,   0.854557991f,
	0.857728601f,   0.860866964f,   0.863972843f,   0.867046237f,   0.870086968f,   0.873094976f,
	0.876070082f,   0.879012227f,   0.881921291f,   0.884797096f,   0.887639642f,   0.890448749f,
	0.893224299f,   0.895966232f,   0.898674488f,   0.901348829f,   0.903989315f,   0.906595707f,
	0.909168005f,   0.91170603f,    0.914209783f,   0.916679084f,   0.919113874f,   0.921514034f,
	0.923879504f,   0.926210225f,   0.928506076f,   0.93076694f,    0.932992816f,   0.935183525f,
	0.937339008f,   0.939459205f,   0.941544056f,   0.943593442f,   0.945607305f,   0.947585583f,
	0.949528158f,   0.95143503f,    0.953306019f,   0.955141187f,   0.956940353f,   0.958703458f,
	0.960430503f,   0.962121427f,   0.963776052f,   0.965394437f,   0.966976464f,   0.968522072f,
	0.970031261f,   0.971503913f,   0.972939968f,   0.974339366f,   0.975702107f,   0.977028131f,
	0.97831738f,    0.979569793f,   0.980785251f,   0.981963873f,   0.983105481f,   0.984210074f,
	0.985277653f,   0.986308098f,   0.987301409f,   0.988257587f,   0.989176512f,   0.990058184f,
	0.990902662f,   0.991709769f,   0.992479563f,   0.993211925f,   0.993906975f,   0.994564593f,
	0.99518472f,    0.995767415f,   0.996312618f,   0.996820271f,   0.997290432f,   0.997723043f,
	0.998118103f,   0.998475552f,   0.99879545f,    0.999077737f,   0.999322414f,   0.999529421f,
	0.999698818f,   0.999830604f,   0.999924719f,   0.999981165f,
};

extern const LegoFloat g_unk0x4b2160;

// FUNCTION: LEGORACERS 0x004778f0
CarModelScreenBase::CarPartPlacement::CarPartPlacement()
{
	LegoFloat angle = 1.57f;

	for (LegoS32 i = 0; i < 8; i++) {
		m_unk0x2a8[i] = angle;
		angle += g_fieldAt0x2308AngleStep;
		if (angle >= g_twoPi) {
			angle -= g_twoPi;
		}
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x004779d0
CarModelScreenBase::CarPartPlacement::~CarPartPlacement()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00477a40
void CarModelScreenBase::CarPartPlacement::Reset()
{
	m_unk0x244 = 1;
	m_unk0x250.m_z = 0.0f;
	m_unk0x250.m_y = 0.0f;
	m_unk0x250.m_x = 0.0f;
	m_unk0x24 = NULL;
	m_unk0x238 = NULL;
	m_unk0x19c = NULL;
	m_unk0x1c = NULL;
	m_unk0x240 = 0;
	m_unk0x248 = 0;
	m_unk0x298 = 0;
	m_unk0x264 = 0;
	m_unk0x268 = 0;
	m_unk0x278 = FALSE;
	m_unk0x26c = 0;
	m_unk0x270 = 0;
	m_unk0x274 = 0;
	m_unk0x290 = FALSE;
	m_unk0x28c = 0;
	m_unk0x29c = 0;
	m_unk0x2a0 = 0;
	m_unk0x2a4 = 0;
	m_unk0x288 = 0;
	m_unk0x2c8 = 0;
	m_unk0x294 = 0;
	m_unk0x2cc = 0;
}

// FUNCTION: LEGORACERS 0x00477ae0
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_00477ae0(CreateParams* p_createParams)
{
	VTable0x08();

	m_unk0x1c = p_createParams->m_screen;
	m_unk0x20 = p_createParams->m_soundGroupBinding;
	m_unk0x24 = p_createParams->m_context;
	m_unk0x250.m_x = p_createParams->m_unk0x1c.m_x;
	m_unk0x250.m_y = p_createParams->m_unk0x1c.m_y;
	m_unk0x250.m_z = p_createParams->m_unk0x1c.m_z;

	if (MenuSceneElement::FUN_0046b300(p_createParams)) {
		FUN_00477cc0(p_createParams->m_unk0x2c);
		FUN_00477dc0();
		FUN_00477bf0();
		FUN_00477c50();
		m_unk0x28.FUN_004513d0(&m_unk0x24->m_unk0x21f4);
		FUN_00477f00(TRUE);
		FUN_004784d0(FALSE);
	}

	return m_unk0x18;
}

// FUNCTION: LEGORACERS 0x00477b80
LegoBool32 CarModelScreenBase::CarPartPlacement::VTable0x08()
{
	if (!m_unk0x18) {
		return TRUE;
	}

	if (m_unk0x1a4.HasModel()) {
		m_unk0x0c->VTable0x48(m_unk0x234);
	}

	m_unk0xa8.VTable0x54();

	if (m_unk0x19c) {
		m_unk0x0c->VTable0x4c(m_unk0x19c);
	}

	if (m_unk0x238) {
		m_unk0x0c->VTable0x48(m_unk0x238);
	}

	return MenuSceneElement::VTable0x08();
}

// FUNCTION: LEGORACERS 0x00477bf0
void CarModelScreenBase::CarPartPlacement::FUN_00477bf0()
{
	GolVec3 targetPosition;
	FUN_00479330(&m_unk0x27c, 0);
	LegoFloat targetZ = m_unk0x250.m_z + 4.0f;
	targetPosition.m_x = m_unk0x250.m_x;
	targetPosition.m_y = m_unk0x250.m_y;
	targetPosition.m_z = targetZ;
	m_unk0x290 = 0;
	m_unk0x288 = 0;
	m_unk0x14->FUN_00465ab0(&m_unk0x27c, &targetPosition);
}

// FUNCTION: LEGORACERS 0x00477c50
void CarModelScreenBase::CarPartPlacement::FUN_00477c50()
{
	m_unk0x234 = m_unk0x0c->VTable0x14();
	if (m_unk0x234 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoS32 maxHighPieceOffset = m_unk0x24->m_pieceLibrary.GetMaxHighPieceOffset();
	m_unk0x234->VTable0x18(m_unk0x10, 2, maxHighPieceOffset * 3, maxHighPieceOffset, 100, 5);
	m_unk0x1a4.VTable0x50(m_unk0x234, g_unk0x4b2e68);
}

// FUNCTION: LEGORACERS 0x00477cc0
void CarModelScreenBase::CarPartPlacement::FUN_00477cc0(undefined4)
{
	DriverCosmetics cosmetics;
	m_unk0x24->m_modelBuilder.SetExpressionMask(0xffff);
	m_unk0x24->m_saveSystem.GetActiveRecord().GetCosmetics(&cosmetics);

	m_unk0x238 = m_unk0x24->m_modelBuilder.BuildDriverModel(&cosmetics, NULL, 0);
	if (m_unk0x238 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x24->m_modelBuilder.ApplyFaceExpression(m_unk0x238, &cosmetics);

	m_unk0x19c = m_unk0x0c->VTable0x18();
	m_unk0x19c->VTable0x10(m_unk0x24->m_modelBuilder.GetBodySceneNode(&cosmetics));
	if (m_unk0x19c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x1a0 = m_unk0x24->m_modelBuilder.GetBodyModelPart(&cosmetics);
	m_unk0xa8.FUN_0040d550(m_unk0x238, m_unk0x19c, m_unk0x1a0, g_unk0x4b2e68);
}

// FUNCTION: LEGORACERS 0x00477dc0
void CarModelScreenBase::CarPartPlacement::FUN_00477dc0()
{
	AwardCinematicScreen::SceneEntityGroup::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));
	createParams.m_chassisModels = &m_unk0x24->m_chassisModels;
	createParams.m_unk0x04 = &m_unk0x24->m_unk0x21f4;
	createParams.m_unk0x08 = m_unk0x24->m_unk0x21f4.GetUnk0x0c();
	createParams.m_unk0x0c = &m_unk0xa8;
	m_unk0x24->m_saveSystem.GetActiveRecord().GetChassisName(createParams.m_chassisName);

	m_unk0x58.FUN_00479510(&createParams);
	m_unk0x58.VTable0x08(m_unk0x250);
	m_unk0x58.VTable0x00();
}

// FUNCTION: LEGORACERS 0x00477e40
void CarModelScreenBase::CarPartPlacement::FUN_00477e40(LegoS32 p_unk0x04)
{
	CarPartSet::Entry* entry = m_unk0x24->m_unk0x21a4.GetSelectedEntry();
	LegoS32 colorRecordIndex;
	m_unk0x25c = p_unk0x04;
	entry->GetChoice(p_unk0x04, &p_unk0x04, &colorRecordIndex);

	LegoPieceLibrary::PieceRecord* pieceRecord = m_unk0x24->m_pieceLibrary.FindPieceRecord(p_unk0x04, TRUE);
	m_unk0x28.SetPiece(pieceRecord, colorRecordIndex, entry->GetPieceType());

	LegoS32 x;
	LegoS32 y;
	LegoS32 rotation;
	m_unk0x28.GetPlacement(&x, &y, &rotation);

	m_unk0x24->m_unk0x21f4.FUN_0049b740(TRUE);
	m_unk0x24->m_unk0x21f4.FUN_0049c230(&m_unk0x28, &m_unk0x1a4);
	m_unk0x1a4.VTable0x08(m_unk0x250);
	m_unk0x240 = 1;
}

// FUNCTION: LEGORACERS 0x00477f00
void CarModelScreenBase::CarPartPlacement::FUN_00477f00(LegoS32 p_unk0x04)
{
	m_unk0x298 = static_cast<LegoS8>(p_unk0x04);
	m_unk0x2c8 = static_cast<LegoFloat>(p_unk0x04);
	FUN_00477f30(m_unk0x2a8[m_unk0x298]);
}

// FUNCTION: LEGORACERS 0x00477f30
void CarModelScreenBase::CarPartPlacement::FUN_00477f30(LegoFloat p_unk0x04)
{
	GolVec3 direction;
	GolVec3 up;

	direction.m_x = 1.0f;
	direction.m_y = 0.0f;
	direction.m_z = 0.0f;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;

	GolMath::FUN_004496a0(&direction, &direction, &up, p_unk0x04);
	m_unk0x58.VTable0x40(direction, up);
	m_unk0x1a4.VTable0x40(direction, up);
}

// FUNCTION: LEGORACERS 0x00477fc0
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_00477fc0(LegoFloat p_delta)
{
	if ((m_unk0x248 & c_flagRotatingAroundCar) || p_delta == 0.0f) {
		return FALSE;
	}

	m_unk0x2c8 += p_delta;
	if (m_unk0x2c8 < 0.0f) {
		m_unk0x2c8 += 8.0f;
	}
	else if (m_unk0x2c8 >= 8.0f) {
		m_unk0x2c8 -= 8.0f;
	}

	LegoS32 index = static_cast<LegoS32>(m_unk0x2c8);
	m_unk0x29c = m_unk0x2a8[index] + ((m_unk0x2c8 - index) * g_fieldAt0x2308AngleStep);
	FUN_00477f30(m_unk0x29c);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00478080
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_00478080(LegoS32 p_delta, LegoBool32 p_setCurrentAngle)
{
	if (m_unk0x248 & c_flagRotatingAroundCar) {
		return FALSE;
	}

	m_unk0x248 |= c_flagRotatingAroundCar;
	m_unk0x2a0 = 150;
	m_unk0x2a4 = 150;

	if (p_setCurrentAngle) {
		m_unk0x29c = m_unk0x2a8[m_unk0x298];
	}

	m_unk0x298 += static_cast<LegoS8>(p_delta);
	if (m_unk0x298 >= 0) {
		m_unk0x298 %= 8;
	}
	else {
		m_unk0x298 += 8;
	}

	m_unk0x2c8 = m_unk0x298;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00478120
void CarModelScreenBase::CarPartPlacement::FUN_00478120()
{
	if (m_unk0x248 & c_flagRotatingAroundCar) {
		return;
	}

	LegoS32 index = static_cast<LegoS32>(m_unk0x2c8 + 0.5f);
	if (index == 8) {
		index = 0;
	}

	if (index != m_unk0x298 || static_cast<LegoFloat>(index) != m_unk0x2c8) {
		FUN_00478080(index - m_unk0x298, FALSE);
	}
}

// FUNCTION: LEGORACERS 0x00478180
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_00478180(LegoFloat p_delta)
{
	if ((m_unk0x248 & c_flagPitchChanging) || p_delta == 0.0f) {
		return FALSE;
	}

	if (p_delta > 0.0f) {
		if (m_unk0x288 >= g_violetShoalTwo) {
			return FALSE;
		}
	}
	else if (m_unk0x288 <= 0.0f) {
		return FALSE;
	}

	m_unk0x288 += p_delta;
	if (m_unk0x288 < 0.0f) {
		m_unk0x288 = 0.0f;
	}
	else if (m_unk0x288 > g_violetShoalTwo) {
		m_unk0x288 = 2.0f;
	}

	LegoS32 index = static_cast<LegoS32>(m_unk0x288);
	if (index == 2) {
		index = 1;
	}

	LegoFloat interpolation = m_unk0x288 - static_cast<LegoFloat>(index);
	GolVec3 minPosition;
	GolVec3 maxPosition;
	FUN_00479330(&minPosition, index);
	FUN_00479330(&maxPosition, index + 1);

	GolVec3 targetPosition;
	LegoFloat targetZ = m_unk0x250.m_z;
	targetZ += 4.0f;
	m_unk0x27c.m_x = ((maxPosition.m_x - minPosition.m_x) * interpolation) + minPosition.m_x;
	targetPosition.m_x = m_unk0x250.m_x;
	targetPosition.m_y = m_unk0x250.m_y;
	m_unk0x27c.m_y = ((maxPosition.m_y - minPosition.m_y) * interpolation) + minPosition.m_y;
	m_unk0x27c.m_z = ((maxPosition.m_z - minPosition.m_z) * interpolation) + minPosition.m_z;
	targetPosition.m_z = targetZ;
	m_unk0x14->FUN_00465ab0(&m_unk0x27c, &targetPosition);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004782f0
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_004782f0(LegoS32 p_delta, LegoBool32 p_setCurrentPosition)
{
	if (m_unk0x248 & c_flagPitchChanging) {
		return FALSE;
	}

	if ((p_delta < 0 && m_unk0x290 == 0) || (p_delta > 0 && m_unk0x290 == 2)) {
		return FALSE;
	}

	if (p_setCurrentPosition) {
		FUN_00479330(&m_unk0x27c, m_unk0x290);
	}

	if (p_delta < 0) {
		if (-p_delta > m_unk0x290) {
			m_unk0x290 = 0;
		}
		else {
			m_unk0x290 += static_cast<LegoS8>(p_delta);
		}
	}
	else {
		m_unk0x290 += static_cast<LegoU8>(p_delta);
		if (m_unk0x290 >= 2) {
			m_unk0x290 = 2;
		}
	}

	LegoU32 flags = m_unk0x248;
	flags |= c_flagPitchChanging;
	LegoS32 pitchIndex = m_unk0x290;
	m_unk0x28c = 300;
	m_unk0x248 = flags;
	m_unk0x288 = static_cast<LegoFloat>(pitchIndex);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004783d0
void CarModelScreenBase::CarPartPlacement::FUN_004783d0()
{
	if (m_unk0x248 & c_flagPitchChanging) {
		return;
	}

	GolVec3 cameraPosition;
	m_unk0x14->GetUnk0x64()->GetTransform()->GetPosition(&cameraPosition);

	LegoU32 closestIndex = 0;
	GolVec3 position;
	FUN_00479330(&position, 0);
	LegoFloat closestDistance = GOL_SQUARED(cameraPosition.m_z - position.m_z) +
								GOL_SQUARED(cameraPosition.m_y - position.m_y) +
								GOL_SQUARED(cameraPosition.m_x - position.m_x);

	for (LegoU32 i = 1; i < 3; i++) {
		FUN_00479330(&position, i);
		LegoFloat distance = GOL_SQUARED(cameraPosition.m_z - position.m_z) +
							 GOL_SQUARED(cameraPosition.m_y - position.m_y) +
							 GOL_SQUARED(cameraPosition.m_x - position.m_x);
		if (distance < closestDistance) {
			closestDistance = distance;
			closestIndex = i;
		}
	}

	if (closestDistance == 0.0f) {
		m_unk0x290 = static_cast<LegoU8>(closestIndex);
	}
	else {
		FUN_004782f0(closestIndex - m_unk0x290, FALSE);
	}
}

// FUNCTION: LEGORACERS 0x004784d0
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_004784d0(LegoBool32 p_rotateFirst)
{
	if (m_unk0x248 & c_flagPitchChanging) {
		return FALSE;
	}

	if (p_rotateFirst) {
		if (!FUN_00478080(9 - m_unk0x298, TRUE)) {
			return FALSE;
		}

		FUN_00479330(&m_unk0x27c, m_unk0x290);
		m_unk0x28c = 300;
	}
	else {
		m_unk0x28c = 1;
	}

	m_unk0x290 = 1;
	m_unk0x248 |= c_flagPitchChanging;
	m_unk0x288 = 1.0f;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00478560
void CarModelScreenBase::CarPartPlacement::FUN_00478560()
{
	m_unk0x28.Rotate();
	m_unk0x24->m_unk0x21f4.FUN_0049b740(TRUE);
	m_unk0x24->m_unk0x21f4.FUN_0049c230(&m_unk0x28, &m_unk0x1a4);
	m_unk0x1a4.VTable0x08(m_unk0x250);
}

// FUNCTION: LEGORACERS 0x004785b0
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_004785b0(LegoS32 p_delta)
{
	LegoS32 oldX;
	LegoS32 newX;
	LegoS32 oldY;
	LegoS32 newY;
	LegoS32 oldRotation;
	LegoS32 newRotation;

	m_unk0x28.GetPlacement(&oldX, &oldY, &oldRotation);
	m_unk0x28.FUN_00499c20(p_delta);
	m_unk0x28.GetPlacement(&newX, &newY, &newRotation);
	if (oldX == newX && oldY == newY && oldRotation == newRotation) {
		return FALSE;
	}

	m_unk0x24->m_unk0x21f4.FUN_0049b740(TRUE);
	m_unk0x24->m_unk0x21f4.FUN_0049c230(&m_unk0x28, &m_unk0x1a4);
	m_unk0x1a4.VTable0x08(m_unk0x250);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00478670
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_00478670(LegoS32 p_delta)
{
	LegoS32 oldX;
	LegoS32 newX;
	LegoS32 oldY;
	LegoS32 newY;
	LegoS32 oldRotation;
	LegoS32 newRotation;

	m_unk0x28.GetPlacement(&oldX, &oldY, &oldRotation);
	m_unk0x28.FUN_00499c60(p_delta);
	m_unk0x28.GetPlacement(&newX, &newY, &newRotation);
	if (oldX == newX && oldY == newY && oldRotation == newRotation) {
		return FALSE;
	}

	m_unk0x24->m_unk0x21f4.FUN_0049b740(TRUE);
	m_unk0x24->m_unk0x21f4.FUN_0049c230(&m_unk0x28, &m_unk0x1a4);
	m_unk0x1a4.VTable0x08(m_unk0x250);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00478730
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_00478730()
{
	LegoS32 x;
	LegoS32 y;
	LegoS32 rotation;
	LegoPieceLibrary::PieceRecord* pieceRecord = m_unk0x28.GetPieceRecord();
	m_unk0x28.GetPlacement(&x, &y, &rotation);

	LegoS32 result = m_unk0x24->m_unk0x21f4.FUN_0049a1e0(pieceRecord, x, y, rotation);
	if (result < 0) {
		if (result != -7) {
			m_unk0x20->FUN_0046e970(18);
		}
		else {
			m_unk0x1c->VTable0xc4();
		}

		return FALSE;
	}

	m_unk0x24->m_saveSystem.GetActiveRecord().MarkCarModified();
	m_unk0x248 |= c_flagCommittingPart;
	m_unk0x274 = g_unk0x4b2ed8;
	m_unk0x24c = 2500;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004787e0
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_004787e0(
	LegoS32* p_unk0x04,
	LegoS32* p_unk0x08,
	LegoS32* p_unk0x0c
)
{
	CarBuildModel* carModel = &m_unk0x24->m_unk0x21f4;
	LegoS32 count = carModel->GetPlacedPieceCount();

	if (count == 1) {
		m_unk0x20->FUN_0046e970(18);
		*p_unk0x0c = 0;
		*p_unk0x08 = 0;
		*p_unk0x04 = 0;
		return FALSE;
	}

	LegoPieceLibrary::PieceRecord* pieceRecord;
	LegoS32 x;
	LegoS32 y;
	LegoS32 anchor;
	LegoS32 rotation;
	carModel->FUN_0049bce0(count - 1, &pieceRecord, &x, &y, &anchor, &rotation, p_unk0x0c, p_unk0x04);
	carModel->FUN_0049bdc0();
	carModel->FUN_0049b740(TRUE);
	carModel->FUN_0049b920(1, 127);
	m_unk0x28.SetPiece(pieceRecord, *p_unk0x0c, 0);
	m_unk0x28.SetPlacement(x, y, rotation, 0);
	carModel->FUN_0049c230(&m_unk0x28, &m_unk0x1a4);
	*p_unk0x08 = pieceRecord->m_pieceType;
	m_unk0x24->m_saveSystem.GetActiveRecord().MarkCarModified();
	m_unk0x20->FUN_0046e970(13);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004788f0
LegoBool32 CarModelScreenBase::CarPartPlacement::VTable0x0c()
{
	ColorRGBA originalColor = {0x78, 0x78, 0x78, 0xff};
	ColorRGBA highlightColor = {0xb4, 0xb4, 0xb4, 0xff};
	GolRenderDevice::MaterialColor* material = m_unk0x10->GetCurrentMaterialColor();

	if (material == NULL) {
		m_unk0x23c.SetColor(originalColor);
		m_unk0x10->VTable0x2c(&m_unk0x23c);
		material = &m_unk0x23c;
	}

	originalColor = material->GetColor();
	if (m_unk0x294 == 2) {
		material->SetColor(highlightColor);
		m_unk0x10->VTable0x60();
	}

	m_unk0x58.VTable0x1c(*m_unk0x10);

	if (m_unk0x294 == 2) {
		material->SetColor(originalColor);
		m_unk0x10->VTable0x60();
	}

	if (m_unk0x240) {
		if (m_unk0x244) {
			m_unk0x24->m_unk0x21f4.FUN_0049bdd0(m_unk0x10, 0.1f);
		}

		GolModelEntity* entity = &m_unk0x1a4;
		GolVec3 position;
		position.m_x = m_unk0x250.m_x;
		position.m_y = m_unk0x250.m_y;
		position.m_z = m_unk0x26c;
		entity->VTable0x08(position);

		if (m_unk0x294 == 1) {
			material->SetColor(highlightColor);
			m_unk0x10->VTable0x60();
		}

		if (!(m_unk0x248 & (c_flagCommittingPart | c_flagResettingView))) {
			if ((m_unk0x278 & c_placementFeedbackMask) && m_unk0x290 != 2) {
				m_unk0x10->SetAlphaOverride(0x40, 0);
				m_unk0x10->VTable0x94(entity);
				m_unk0x10->ClearAlphaOverride();
			}
		}

		LegoU32 alpha;
		if (m_unk0x278 & c_placementFeedbackMask) {
			alpha = 0x96;
			LegoFloat value = m_unk0x26c - m_unk0x270 - 1.2f;

			if (value < 1.2f && m_unk0x290 != 2) {
				if (value < 0.0f) {
					alpha = 0;
				}
				else {
					LegoFloat alphaValue = value;
					alphaValue /= 1.2f;
					alphaValue *= 150.0f;
					alpha = static_cast<LegoU32>(alphaValue);
				}
			}
		}
		else {
			LegoFloat scaledTime = static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x268));
			scaledTime *= 0.001f;
			scaledTime *= g_twoPi;
			scaledTime *= g_negativeRadiansToTableIndex;
			LegoS32 index = (0xffffff00 - static_cast<LegoS32>(scaledTime)) & 0x3ff;
			LegoFloat interpolation = g_cosineTable[index];
			interpolation *= 50.0f;
			alpha = static_cast<LegoU32>(interpolation) + 0x64;
		}

		position.m_z = m_unk0x270;
		entity->VTable0x08(position);

		if (!(m_unk0x248 & (c_flagCommittingPart | c_flagResettingView)) && alpha > 0) {
			m_unk0x10->SetAlphaOverride(alpha, 0);
			m_unk0x10->VTable0x94(entity);
			m_unk0x10->ClearAlphaOverride();
		}

		if (m_unk0x248 & (c_flagCommittingPart | c_flagResettingView)) {
			position.m_z = m_unk0x274;
		}
		else {
			position.m_z = g_unk0x4b2ed8;
		}

		entity->VTable0x08(position);

		if (m_unk0x290 != 2 || (m_unk0x248 & (c_flagCommittingPart | c_flagResettingView))) {
			m_unk0x10->VTable0x94(entity);
		}

		entity->VTable0x08(m_unk0x250);

		if (m_unk0x294 == 1) {
			material->SetColor(originalColor);
			m_unk0x10->VTable0x60();
		}
	}

	if (!(m_unk0x248 & (c_flagCommittingPart | c_flagResettingView))) {
		m_unk0x244 = TRUE;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00478be0
LegoBool32 CarModelScreenBase::CarPartPlacement::VTable0x10(undefined4 p_elapsed)
{
	FUN_00478c70(p_elapsed);

	if (p_elapsed >= m_unk0x268) {
		m_unk0x268 = m_unk0x268 - p_elapsed + 1000;
	}
	else {
		m_unk0x268 -= p_elapsed;
	}

	m_unk0xa8.VTable0x10(p_elapsed);

	if (m_unk0x248) {
		if (m_unk0x248 & c_flagRotatingAroundCar) {
			FUN_00478ef0(p_elapsed);
		}
		if (m_unk0x248 & c_flagPitchChanging) {
			FUN_00478fd0(p_elapsed);
		}
		if (m_unk0x248 & c_flagCommittingPart) {
			FUN_004790f0(p_elapsed);
		}
		if (m_unk0x248 & c_flagResettingView) {
			FUN_00479250(p_elapsed);
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00478c70
void CarModelScreenBase::CarPartPlacement::FUN_00478c70(LegoS32 p_elapsed)
{
	if (m_unk0x248 & (c_flagCommittingPart | c_flagResettingView)) {
		return;
	}

	LegoS32 x;
	LegoS32 y;
	LegoS32 rotation;
	LegoPieceLibrary::PieceRecord* pieceRecord = m_unk0x28.GetPieceRecord();
	m_unk0x28.GetPlacement(&x, &y, &rotation);

	LegoS32 result = m_unk0x24->m_unk0x21f4.FUN_0049a1e0(pieceRecord, x, y, rotation);
	if (result >= 0) {
		if (!m_unk0x278) {
			FUN_00478ec0(0);
		}
	}
	else {
		m_unk0x278 &= ~c_placementFeedbackMask;
		m_unk0x26c = m_unk0x270;
	}

	LegoU8 feedbackFlags = m_unk0x278;
	if (feedbackFlags & c_placementFeedbackMask) {
		if (p_elapsed >= m_unk0x264) {
			if (feedbackFlags & c_placementFeedbackLowering) {
				m_unk0x264 = 0;
				m_unk0x278 = (feedbackFlags & ~c_placementFeedbackLowering) | c_placementFeedbackHold;
			}
			else if (feedbackFlags & c_placementFeedbackHold) {
				FUN_00478e90(p_elapsed - m_unk0x264);
			}
			else if (feedbackFlags & c_placementFeedbackRaising) {
				FUN_00478ec0(p_elapsed - m_unk0x264);
			}
		}
		else {
			m_unk0x264 -= p_elapsed;
		}
	}

	m_unk0x270 = (m_unk0x24->m_unk0x21f4.GetUnk0x2028() * g_carBuildModelHeightScale) + (g_unk0x4b2ed8 - 8.4f);

	feedbackFlags = m_unk0x278;
	if (feedbackFlags & c_placementFeedbackMask) {
		if (feedbackFlags & c_placementFeedbackLowering) {
			LegoFloat delta = static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x26c - m_unk0x270));
			delta *= 0.33333334f;
			if (delta > 1.0f) {
				delta = 1.0f;
			}
			else if (delta < 0.3f) {
				delta = 0.3f;
			}

			delta *= 0.01f;
			LegoFloat elapsed = static_cast<LegoFloat>(p_elapsed);
			delta *= elapsed;
			m_unk0x26c -= delta;
			if (m_unk0x26c <= m_unk0x270) {
				m_unk0x264 = 0;
				m_unk0x26c = m_unk0x270;
			}
		}
		else if (feedbackFlags & c_placementFeedbackRaising) {
			m_unk0x26c += p_elapsed * 0.01f;
			LegoFloat limit = g_unk0x4b2ed8 - (g_carPartHoverHeight + g_carPartHoverHeight);
			if (m_unk0x26c >= limit) {
				m_unk0x264 = 0;
				m_unk0x26c = limit;
			}
		}
	}
	else {
		m_unk0x264 = 2500;
		m_unk0x26c = m_unk0x270;
	}
}

// FUNCTION: LEGORACERS 0x00478e90
void CarModelScreenBase::CarPartPlacement::FUN_00478e90(LegoS32 p_elapsed)
{
	m_unk0x264 = 2500 - p_elapsed;
	m_unk0x278 = (m_unk0x278 & ~(c_placementFeedbackLowering | c_placementFeedbackHold)) | c_placementFeedbackRaising;
}

// FUNCTION: LEGORACERS 0x00478ec0
void CarModelScreenBase::CarPartPlacement::FUN_00478ec0(LegoS32 p_elapsed)
{
	m_unk0x264 = 2500 - p_elapsed;
	m_unk0x278 = (m_unk0x278 & ~(c_placementFeedbackHold | c_placementFeedbackRaising)) | c_placementFeedbackLowering;
}

// FUNCTION: LEGORACERS 0x00478ef0
void CarModelScreenBase::CarPartPlacement::FUN_00478ef0(LegoU32 p_elapsed)
{
	if (m_unk0x2a0 == 0) {
		return;
	}

	if (p_elapsed >= static_cast<LegoU32>(m_unk0x2a0)) {
		m_unk0x2a0 = 0;
		m_unk0x248 &= ~c_flagRotatingAroundCar;
	}
	else {
		m_unk0x2a0 -= p_elapsed;
	}

	LegoFloat scaledTime = static_cast<LegoFloat>(m_unk0x2a0);
	LegoFloat totalTime = static_cast<LegoFloat>(m_unk0x2a4);
	scaledTime /= totalTime;
	scaledTime *= g_halfPi;
	scaledTime *= g_negativeRadiansToTableIndex;
	LegoS32 index = (0xffffff00 - static_cast<LegoS32>(scaledTime)) & 0x3ff;
	LegoFloat interpolation = g_cosineTable[index];
	LegoFloat targetAngle = m_unk0x2a8[m_unk0x298];

	LegoFloat upperLimit = m_unk0x29c;
	upperLimit += g_halfPi;
	if (targetAngle > upperLimit) {
		targetAngle -= g_twoPi;
	}
	else if (targetAngle < m_unk0x29c - g_halfPi) {
		targetAngle += g_twoPi;
	}

	FUN_00477f30(targetAngle + ((m_unk0x29c - targetAngle) * interpolation));
}

// FUNCTION: LEGORACERS 0x00478fd0
void CarModelScreenBase::CarPartPlacement::FUN_00478fd0(LegoU32 p_elapsed)
{
	if (m_unk0x28c == 0) {
		return;
	}

	if (p_elapsed >= static_cast<LegoU32>(m_unk0x28c)) {
		m_unk0x28c = 0;
		m_unk0x248 &= ~c_flagPitchChanging;
	}
	else {
		m_unk0x28c -= p_elapsed;
	}

	LegoFloat scaledTime = static_cast<LegoFloat>(m_unk0x28c);
	scaledTime *= g_unk0x4b2160;
	scaledTime *= g_halfPi;
	scaledTime *= g_negativeRadiansToTableIndex;
	LegoS32 index = (0xffffff00 - static_cast<LegoS32>(scaledTime)) & 0x3ff;
	LegoFloat interpolation = g_cosineTable[index];

	GolVec3 targetPosition;
	FUN_00479330(&targetPosition, m_unk0x290);

	GolVec3 delta;
	delta.m_x = m_unk0x27c.m_x - targetPosition.m_x;
	delta.m_y = m_unk0x27c.m_y - targetPosition.m_y;

	GolVec3 lookAt;
	lookAt.m_x = m_unk0x250.m_x;
	lookAt.m_y = m_unk0x250.m_y;

	GolVec3 position;
	delta.m_z = m_unk0x27c.m_z - targetPosition.m_z;
	position.m_x = targetPosition.m_x + (delta.m_x * interpolation);
	position.m_y = targetPosition.m_y + (delta.m_y * interpolation);
	position.m_z = targetPosition.m_z + (delta.m_z * interpolation);
	lookAt.m_z = m_unk0x250.m_z + 4.0f;
	m_unk0x14->FUN_00465ab0(&position, &lookAt);
}

// FUNCTION: LEGORACERS 0x004790f0
void CarModelScreenBase::CarPartPlacement::FUN_004790f0(LegoS32 p_elapsed)
{
	if (p_elapsed >= m_unk0x24c) {
		LegoPieceLibrary::PieceRecord* pieceRecord = m_unk0x28.GetPieceRecord();
		LegoS32 x;
		LegoS32 y;
		LegoS32 rotation;
		m_unk0x28.GetPlacement(&x, &y, &rotation);

		m_unk0x248 &= ~c_flagCommittingPart;
		m_unk0x24c = 0;
		m_unk0x58.FUN_10026fa0(-1.0f);
		m_unk0x58.VTable0x00();

		m_unk0x24->m_unk0x21f4.FUN_0049a160(
			pieceRecord,
			x,
			y,
			rotation,
			m_unk0x28.GetColorRecordIndex(),
			m_unk0x24->m_unk0x21a4.GetSelectedEntry()->GetPieceType()
		);
		m_unk0x24->m_unk0x21f4.FUN_0049b740(TRUE);
		m_unk0x24->m_unk0x21f4.FUN_0049b920(1, 127);
		m_unk0x1c->VTable0x10(m_unk0x14);

		if (m_unk0x24->m_unk0x21f4.GetUnk0xdc()) {
			m_unk0x1c->VTable0xc4();
			m_unk0x24->m_unk0x21f4.FUN_0049bdc0();
			m_unk0x24->m_unk0x21f4.FUN_0049b740(TRUE);
			m_unk0x24->m_unk0x21f4.FUN_0049b920(1, 127);
		}
		else {
			m_unk0x20->FUN_0046e970(10);
		}
	}
	else {
		m_unk0x24c -= p_elapsed;
	}

	m_unk0x274 -= p_elapsed * 0.01f;
	if (m_unk0x274 < m_unk0x270) {
		m_unk0x24c = 0;
		m_unk0x274 = m_unk0x270;
	}
}

// FUNCTION: LEGORACERS 0x00479250
void CarModelScreenBase::CarPartPlacement::FUN_00479250(LegoS32 p_elapsed)
{
	if (p_elapsed >= m_unk0x24c) {
		LegoU32 flags = m_unk0x248 & ~c_flagResettingView;
		m_unk0x24c = 0;
		m_unk0x248 = flags;
		m_unk0x1c->VTable0x10(m_unk0x14);
	}
	else {
		m_unk0x24c -= p_elapsed;
	}

	m_unk0x274 += p_elapsed * 0.006f;
	if (m_unk0x274 > g_unk0x4b2ed8) {
		m_unk0x24c = 0;
		m_unk0x274 = g_unk0x4b2ed8;
	}
}

// FUNCTION: LEGORACERS 0x004792d0
void CarModelScreenBase::CarPartPlacement::FUN_004792d0()
{
	m_unk0x24c = 2000;
	m_unk0x244 = 0;
	m_unk0x248 |= 8;
	m_unk0x274 = m_unk0x270;
}

// FUNCTION: LEGORACERS 0x00479300
void CarModelScreenBase::CarPartPlacement::FUN_00479300()
{
	m_unk0x294 = 2;
}

// FUNCTION: LEGORACERS 0x00479310
void CarModelScreenBase::CarPartPlacement::FUN_00479310()
{
	m_unk0x294 = 1;
}

// FUNCTION: LEGORACERS 0x00479320
void CarModelScreenBase::CarPartPlacement::FUN_00479320()
{
	m_unk0x294 = 0;
}

// FUNCTION: LEGORACERS 0x00479330
void CarModelScreenBase::CarPartPlacement::FUN_00479330(GolVec3* p_dest, LegoS32 p_index)
{
	m_unk0x2cc = (m_unk0x58.FUN_10028710() - 5.9f) / (8.5f - 5.9f);
	if (m_unk0x2cc > 1.0f) {
		m_unk0x2cc = 1.0f;
	}
	else if (m_unk0x2cc < 0.0f) {
		m_unk0x2cc = 0.0f;
	}

	LegoFloat value = g_carPartCameraPositions[p_index * 3];
	value *= 1.0f - m_unk0x2cc;
	value += g_carPartCameraPositions[p_index * 3 + 10] * m_unk0x2cc;
	p_dest->m_x = value;

	value = g_carPartCameraPositions[p_index * 3 + 1];
	value *= 1.0f - m_unk0x2cc;
	value += g_carPartCameraPositions[p_index * 3 + 11] * m_unk0x2cc;
	p_dest->m_y = value;

	value = g_carPartCameraPositions[p_index * 3 + 2];
	value *= 1.0f - m_unk0x2cc;
	value += g_carPartCameraPositions[p_index * 3 + 12] * m_unk0x2cc;
	p_dest->m_z = value;
}
