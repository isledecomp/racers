#include "whitefalcon0x140.h"

#include "amberhaze0x1c.h"
#include "cinderbasin0x28.h"
#include "falcontextureformat.h"
#include "hypnoticnoise0x1c.h"
#include "magentaribbon0x20.h"

#include <string.h>

// GLOBAL: GOLDP 0x1005dfec
LegoFloat g_arccosTable[1024] = {
	3.1415927f,  3.079052f,   3.0531323f,  3.0332336f,  3.0164499f,   3.001656f,    2.9882746f,  2.975963f,
	2.9644983f,  2.9537249f,  2.94353f,    2.9338288f,  2.9245548f,   2.9156554f,   2.9070878f,  2.898817f,
	2.8908138f,  2.883053f,   2.8755138f,  2.8681774f,  2.8610282f,   2.854052f,    2.8472369f,  2.8405714f,
	2.8340461f,  2.8276522f,  2.821382f,   2.815228f,   2.8091838f,   2.8032439f,   2.7974024f,  2.7916546f,
	2.785996f,   2.7804222f,  2.7749295f,  2.7695143f,  2.7641733f,   2.7589033f,   2.7537014f,  2.7485647f,
	2.7434912f,  2.7384779f,  2.7335229f,  2.728624f,   2.7237797f,   2.7189872f,   2.7142456f,  2.7095525f,
	2.7049069f,  2.7003071f,  2.6957517f,  2.691239f,   2.6867683f,   2.682338f,    2.6779473f,  2.6735945f,
	2.669279f,   2.6649997f,  2.6607554f,  2.6565456f,  2.652369f,    2.6482248f,   2.6441126f,  2.640031f,
	2.6359799f,  2.631958f,   2.6279647f,  2.6239998f,  2.620062f,    2.6161513f,   2.6122665f,  2.6084077f,
	2.6045737f,  2.6007643f,  2.5969789f,  2.5932171f,  2.5894783f,   2.5857618f,   2.5820677f,  2.5783951f,
	2.5747437f,  2.5711133f,  2.5675032f,  2.5639133f,  2.560343f,    2.5567918f,   2.5532598f,  2.5497463f,
	2.546251f,   2.5427737f,  2.539314f,   2.5358717f,  2.5324464f,   2.529038f,    2.5256457f,  2.52227f,
	2.5189099f,  2.5155654f,  2.5122366f,  2.5089226f,  2.5056238f,   2.5023396f,   2.4990697f,  2.495814f,
	2.4925725f,  2.4893448f,  2.4861305f,  2.4829297f,  2.479742f,    2.4765675f,   2.4734056f,  2.4702566f,
	2.4671197f,  2.4639952f,  2.4608827f,  2.4577823f,  2.4546933f,   2.4516163f,   2.4485505f,  2.4454958f,
	2.4424527f,  2.4394202f,  2.4363987f,  2.4333878f,  2.4303875f,   2.4273975f,   2.424418f,   2.4214485f,
	2.418489f,   2.4155395f,  2.4125996f,  2.4096694f,  2.4067488f,   2.4038377f,   2.4009356f,  2.3980429f,
	2.3951592f,  2.3922846f,  2.3894186f,  2.3865616f,  2.383713f,    2.3808732f,   2.3780417f,  2.3752186f,
	2.3724039f,  2.369597f,   2.3667984f,  2.3640077f,  2.3612251f,   2.3584499f,   2.3556828f,  2.3529232f,
	2.350171f,   2.3474264f,  2.3446894f,  2.3419592f,  2.3392367f,   2.3365211f,   2.3338125f,  2.3311112f,
	2.3284166f,  2.3257289f,  2.3230479f,  2.3203735f,  2.317706f,    2.315045f,    2.3123906f,  2.3097425f,
	2.3071008f,  2.3044653f,  2.3018363f,  2.2992132f,  2.2965965f,   2.2939856f,   2.2913809f,  2.2887821f,
	2.286189f,   2.283602f,   2.2810206f,  2.278445f,   2.275875f,    2.2733107f,   2.270752f,   2.2681987f,
	2.2656507f,  2.2631085f,  2.2605712f,  2.2580395f,  2.255513f,    2.2529917f,   2.2504754f,  2.2479644f,
	2.2454584f,  2.2429574f,  2.2404613f,  2.23797f,    2.2354839f,   2.2330027f,   2.230526f,   2.228054f,
	2.2255869f,  2.2231245f,  2.2206666f,  2.2182133f,  2.2157645f,   2.2133203f,   2.2108805f,  2.208445f,
	2.2060142f,  2.2035875f,  2.2011652f,  2.1987472f,  2.1963334f,   2.1939237f,   2.1915183f,  2.1891172f,
	2.1867199f,  2.1843266f,  2.1819377f,  2.1795526f,  2.1771712f,   2.1747942f,   2.1724207f,  2.1700513f,
	2.1676855f,  2.1653237f,  2.1629655f,  2.1606112f,  2.1582606f,   2.1559136f,   2.1535702f,  2.1512306f,
	2.1488943f,  2.1465619f,  2.1442327f,  2.1419072f,  2.139585f,    2.1372664f,   2.134951f,   2.1326394f,
	2.1303308f,  2.1280258f,  2.1257238f,  2.1234252f,  2.12113f,     2.1188378f,   2.116549f,   2.1142633f,
	2.1119807f,  2.1097014f,  2.107425f,   2.1051517f,  2.1028814f,   2.1006143f,   2.0983503f,  2.0960891f,
	2.0938308f,  2.0915756f,  2.0893233f,  2.0870738f,  2.0848272f,   2.0825834f,   2.0803423f,  2.0781043f,
	2.0758688f,  2.0736363f,  2.0714064f,  2.0691793f,  2.0669549f,   2.064733f,    2.062514f,   2.0602975f,
	2.0580838f,  2.0558724f,  2.0536637f,  2.0514576f,  2.0492539f,   2.0470529f,   2.0448542f,  2.042658f,
	2.0404644f,  2.0382733f,  2.0360844f,  2.033898f,   2.0317142f,   2.0295324f,   2.027353f,   2.0251763f,
	2.0230014f,  2.0208292f,  2.018659f,   2.0164912f,  2.0143256f,   2.0121624f,   2.0100012f,  2.0078423f,
	2.0056856f,  2.003531f,   2.0013783f,  1.999228f,   1.9970798f,   1.9949336f,   1.9927896f,  1.9906476f,
	1.9885076f,  1.9863697f,  1.9842337f,  1.9820999f,  1.979968f,    1.977838f,    1.97571f,    1.9735839f,
	1.9714597f,  1.9693376f,  1.9672172f,  1.9650987f,  1.9629822f,   1.9608674f,   1.9587545f,  1.9566435f,
	1.9545342f,  1.9524267f,  1.950321f,   1.948217f,   1.9461149f,   1.9440144f,   1.9419158f,  1.9398187f,
	1.9377234f,  1.9356298f,  1.9335378f,  1.9314476f,  1.929359f,    1.927272f,    1.9251866f,  1.9231029f,
	1.9210206f,  1.9189401f,  1.916861f,   1.9147836f,  1.9127076f,   1.9106332f,   1.9085604f,  1.906489f,
	1.9044192f,  1.9023508f,  1.9002838f,  1.8982184f,  1.8961544f,   1.8940918f,   1.8920307f,  1.889971f,
	1.8879126f,  1.8858557f,  1.8838001f,  1.8817459f,  1.8796932f,   1.8776416f,   1.8755914f,  1.8735427f,
	1.8714951f,  1.8694489f,  1.8674039f,  1.8653603f,  1.8633178f,   1.8612767f,   1.8592368f,  1.8571981f,
	1.8551607f,  1.8531245f,  1.8510895f,  1.8490556f,  1.847023f,    1.8449914f,   1.8429612f,  1.840932f,
	1.8389039f,  1.836877f,   1.8348513f,  1.8328266f,  1.830803f,    1.8287805f,   1.8267591f,  1.8247387f,
	1.8227195f,  1.8207012f,  1.8186841f,  1.8166679f,  1.8146527f,   1.8126386f,   1.8106254f,  1.8086133f,
	1.8066021f,  1.804592f,   1.8025827f,  1.8005744f,  1.798567f,    1.7965608f,   1.7945552f,  1.7925507f,
	1.790547f,   1.7885443f,  1.7865424f,  1.7845414f,  1.7825413f,   1.780542f,    1.7785436f,  1.776546f,
	1.7745492f,  1.7725533f,  1.7705582f,  1.768564f,   1.7665704f,   1.7645777f,   1.7625858f,  1.7605946f,
	1.7586042f,  1.7566146f,  1.7546257f,  1.7526375f,  1.75065f,     1.7486633f,   1.7466773f,  1.744692f,
	1.7427074f,  1.7407234f,  1.7387401f,  1.7367575f,  1.7347755f,   1.7327943f,   1.7308136f,  1.7288336f,
	1.7268542f,  1.7248755f,  1.7228973f,  1.7209197f,  1.7189428f,   1.7169663f,   1.7149905f,  1.7130152f,
	1.7110405f,  1.7090664f,  1.7070928f,  1.7051197f,  1.7031472f,   1.7011752f,   1.6992036f,  1.6972326f,
	1.6952621f,  1.693292f,   1.6913226f,  1.6893535f,  1.6873848f,   1.6854167f,   1.6834489f,  1.6814816f,
	1.6795148f,  1.6775483f,  1.6755823f,  1.6736166f,  1.6716515f,   1.6696867f,   1.6677222f,  1.6657581f,
	1.6637944f,  1.6618311f,  1.6598681f,  1.6579055f,  1.6559432f,   1.6539812f,   1.6520195f,  1.6500582f,
	1.6480972f,  1.6461364f,  1.6441759f,  1.6422157f,  1.6402559f,   1.6382962f,   1.6363369f,  1.6343777f,
	1.6324189f,  1.6304603f,  1.6285019f,  1.6265436f,  1.6245857f,   1.622628f,    1.6206703f,  1.618713f,
	1.6167558f,  1.6147988f,  1.612842f,   1.6108853f,  1.6089287f,   1.6069723f,   1.6050161f,  1.60306f,
	1.601104f,   1.5991482f,  1.5971924f,  1.5952367f,  1.5932811f,   1.5913256f,   1.5893703f,  1.5874149f,
	1.5854596f,  1.5835044f,  1.5815492f,  1.5795941f,  1.577639f,    1.575684f,    1.5737289f,  1.5717739f,
	1.5698189f,  1.5678638f,  1.5659087f,  1.5639536f,  1.5619986f,   1.5600435f,   1.5580883f,  1.556133f,
	1.5541778f,  1.5522225f,  1.550267f,   1.5483116f,  1.546356f,    1.5444003f,   1.5424446f,  1.5404886f,
	1.5385326f,  1.5365765f,  1.5346203f,  1.5326639f,  1.5307074f,   1.5287507f,   1.5267938f,  1.5248369f,
	1.5228796f,  1.5209223f,  1.5189648f,  1.517007f,   1.515049f,    1.5130908f,   1.5111324f,  1.5091738f,
	1.5072149f,  1.5052558f,  1.5032964f,  1.5013368f,  1.4993769f,   1.4974167f,   1.4954562f,  1.4934955f,
	1.4915345f,  1.4895731f,  1.4876114f,  1.4856495f,  1.4836872f,   1.4817245f,   1.4797616f,  1.4777982f,
	1.4758345f,  1.4738704f,  1.4719059f,  1.4699411f,  1.467976f,    1.4660103f,   1.4640443f,  1.4620779f,
	1.460111f,   1.4581437f,  1.456176f,   1.4542079f,  1.4522393f,   1.4502702f,   1.4483006f,  1.4463305f,
	1.44436f,    1.442389f,   1.4404175f,  1.4384454f,  1.4364729f,   1.4344999f,   1.4325262f,  1.4305521f,
	1.4285774f,  1.4266021f,  1.4246264f,  1.42265f,    1.420673f,    1.4186953f,   1.4167172f,  1.4147384f,
	1.4127591f,  1.410779f,   1.4087983f,  1.4068171f,  1.4048351f,   1.4028525f,   1.4008693f,  1.3988854f,
	1.3969007f,  1.3949153f,  1.3929293f,  1.3909426f,  1.3889552f,   1.3869671f,   1.384978f,   1.3829885f,
	1.380998f,   1.3790069f,  1.377015f,   1.3750222f,  1.3730288f,   1.3710344f,   1.3690393f,  1.3670434f,
	1.3650466f,  1.363049f,   1.3610506f,  1.3590513f,  1.3570513f,   1.3550503f,   1.3530484f,  1.3510456f,
	1.3490419f,  1.3470374f,  1.345032f,   1.3430256f,  1.3410182f,   1.3390099f,   1.3370007f,  1.3349905f,
	1.3329793f,  1.3309672f,  1.3289541f,  1.3269399f,  1.3249248f,   1.3229086f,   1.3208914f,  1.3188732f,
	1.3168539f,  1.3148335f,  1.3128121f,  1.3107897f,  1.3087661f,   1.3067414f,   1.3047156f,  1.3026887f,
	1.3006607f,  1.2986315f,  1.2966012f,  1.2945697f,  1.2925371f,   1.2905033f,   1.2884681f,  1.2864319f,
	1.2843945f,  1.2823559f,  1.280316f,   1.2782748f,  1.2762324f,   1.2741888f,   1.2721438f,  1.2700976f,
	1.2680501f,  1.2660012f,  1.2639511f,  1.2618996f,  1.2598467f,   1.2577925f,   1.2557369f,  1.25368f,
	1.2516217f,  1.2495619f,  1.2475008f,  1.2454382f,  1.2433742f,   1.2413088f,   1.2392418f,  1.2371736f,
	1.2351036f,  1.2330322f,  1.2309594f,  1.228885f,   1.2268091f,   1.2247317f,   1.2226527f,  1.220572f,
	1.2184899f,  1.2164061f,  1.2143207f,  1.2122337f,  1.2101451f,   1.2080548f,   1.2059629f,  1.2038692f,
	1.2017739f,  1.199677f,   1.1975782f,  1.1954778f,  1.1933756f,   1.1912717f,   1.1891659f,  1.1870584f,
	1.1849493f,  1.1828382f,  1.1807252f,  1.1786106f,  1.1764939f,   1.1743754f,   1.1722552f,  1.1701329f,
	1.1680087f,  1.1658827f,  1.1637547f,  1.1616247f,  1.1594927f,   1.1573589f,   1.155223f,   1.153085f,
	1.1509451f,  1.1488031f,  1.146659f,   1.1445129f,  1.1423646f,   1.1402143f,   1.1380618f,  1.1359072f,
	1.1337504f,  1.1315914f,  1.1294303f,  1.127267f,   1.1251013f,   1.1229335f,   1.1207634f,  1.1185911f,
	1.1164165f,  1.1142395f,  1.1120602f,  1.1098785f,  1.1076945f,   1.1055082f,   1.1033194f,  1.1011281f,
	1.0989345f,  1.0967383f,  1.0945398f,  1.0923387f,  1.0901351f,   1.0879289f,   1.0857203f,  1.083509f,
	1.0812951f,  1.0790787f,  1.0768595f,  1.0746378f,  1.0724133f,   1.0701861f,   1.0679563f,  1.0657238f,
	1.0634884f,  1.0612502f,  1.0590093f,  1.0567656f,  1.0545189f,   1.0522695f,   1.0500171f,  1.0477618f,
	1.0455036f,  1.0432425f,  1.0409783f,  1.0387111f,  1.036441f,    1.0341676f,   1.0318913f,  1.0296119f,
	1.0273293f,  1.0250436f,  1.0227548f,  1.0204626f,  1.0181674f,   1.0158688f,   1.013567f,   1.0112618f,
	1.0089533f,  1.0066414f,  1.0043262f,  1.0020076f,  0.99968547f,  0.99735987f,  0.9950308f,  0.99269825f,
	0.9903621f,  0.98802239f, 0.98567903f, 0.98333204f, 0.9809814f,   0.978627f,    0.97626895f, 0.97390705f,
	0.9715414f,  0.96917194f, 0.9667986f,  0.96442133f, 0.96204019f,  0.95965505f,  0.9572659f,  0.95487279f,
	0.95247555f, 0.95007426f, 0.94766885f, 0.9452592f,  0.94284546f,  0.9404274f,   0.93800509f, 0.93557847f,
	0.93314749f, 0.93071216f, 0.92827237f, 0.92582816f, 0.92337936f,  0.92092609f,  0.91846824f, 0.91600573f,
	0.91353858f, 0.9110667f,  0.90859008f, 0.90610868f, 0.90362245f,  0.90113133f,  0.89863527f, 0.8961343f,
	0.89362824f, 0.8911172f,  0.888601f,   0.88607967f, 0.88355315f,  0.8810213f,   0.87848425f, 0.8759418f,
	0.87339395f, 0.87084067f, 0.8682819f,  0.86571753f, 0.86314756f,  0.86057198f,  0.8579906f,  0.85540348f,
	0.85281056f, 0.85021174f, 0.84760696f, 0.8449962f,  0.84237939f,  0.8397564f,   0.83712727f, 0.8344919f,
	0.83185017f, 0.8292021f,  0.8265476f,  0.82388657f, 0.821219f,    0.8185448f,   0.81586385f, 0.81317616f,
	0.81048155f, 0.80778009f, 0.80507159f, 0.802356f,   0.7996333f,   0.79690337f,  0.79416615f, 0.79142153f,
	0.78866947f, 0.78590983f, 0.7831426f,  0.7803676f,  0.77758485f,  0.7747942f,   0.7719956f,  0.76918888f,
	0.76637405f, 0.76355094f, 0.76071948f, 0.75787956f, 0.7550311f,   0.75217396f,  0.7493081f,  0.74643338f,
	0.7435497f,  0.74065697f, 0.73775506f, 0.73484379f, 0.73192316f,  0.728993f,    0.72605324f, 0.72310364f,
	0.72014415f, 0.7171747f,  0.71419507f, 0.71120518f, 0.70820487f,  0.705194f,    0.70217246f, 0.69914007f,
	0.6960967f,  0.6930422f,  0.68997645f, 0.6868993f,  0.68381047f,  0.68070996f,  0.6775975f,  0.67447299f,
	0.67133623f, 0.66818696f, 0.6650251f,  0.6618505f,  0.65866286f,  0.65546209f,  0.65224785f, 0.64902008f,
	0.64577854f, 0.64252293f, 0.63925314f, 0.6359689f,  0.63266999f,  0.62935615f,  0.6260272f,  0.6226828f,
	0.61932278f, 0.6159468f,  0.6125547f,  0.60914618f, 0.60572088f,  0.60227853f,  0.5988189f,  0.59534156f,
	0.59184635f, 0.58833283f, 0.58480078f, 0.5812497f,  0.57767934f,  0.57408935f,  0.57047933f, 0.5668488f,
	0.56319755f, 0.559525f,   0.55583078f, 0.55211449f, 0.5483756f,   0.5446137f,   0.54082835f, 0.53701895f,
	0.533185f,   0.529326f,   0.52544135f, 0.5215305f,  0.5175929f,   0.5136278f,   0.50963473f, 0.50561285f,
	0.5015615f,  0.49748009f, 0.49336773f, 0.48922369f, 0.48504713f,  0.4808372f,   0.47659302f, 0.47231364f,
	0.46799815f, 0.46364546f, 0.45925456f, 0.45482433f, 0.45035356f,  0.4458411f,   0.4412856f,  0.43668577f,
	0.43204013f, 0.42734718f, 0.4226054f,  0.41781309f, 0.41296846f,  0.40806967f,  0.40311474f, 0.39810154f,
	0.39302787f, 0.38789132f, 0.38268939f, 0.37741932f, 0.37207827f,  0.36666307f,  0.36117044f, 0.35559672f,
	0.34993809f, 0.34419033f, 0.33834887f, 0.33240882f, 0.32636473f,  0.32021073f,  0.31394035f, 0.30754644f,
	0.30102119f, 0.29435578f, 0.2875405f,  0.28056437f, 0.27341515f,  0.26607883f,  0.25853947f, 0.25077879f,
	0.24277551f, 0.23450482f, 0.22593732f, 0.21703789f, 0.20776382f,  0.19806251f,  0.18786778f, 0.1770944f,
	0.16562952f, 0.15331803f, 0.13993669f, 0.12514272f, 0.108359076f, 0.088460378f, 0.06254073f, 0.0f,
};

DECOMP_SIZE_ASSERT(WhiteFalcon0x140::TexturedVertex, 0x18)
DECOMP_SIZE_ASSERT(WhiteFalcon0x140::RenderTargetInfo, 0x2e)
DECOMP_SIZE_ASSERT(WhiteFalcon0x140, 0x140)

// FUNCTION: GOLDP 0x10028840
WhiteFalcon0x140::WhiteFalcon0x140()
{
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_countTextureFormats = 0;
	m_textureFormats = NULL;
	m_unk0x38 = NULL;
	m_unk0x3c = NULL;
	m_unk0x40 = NULL;
	m_unk0x44 = NULL;
	m_nextDrawStateRenderer = NULL;
	m_unk0x0c = NULL;
	m_unk0x04 = 0;
	m_unk0x0a = 0;
	::memset(m_unk0x4c, 0, sizeof(m_unk0x4c));
	m_unk0x11c = 0;
	m_unk0x120 = 0;
	::memset(&m_unk0x124, 0, sizeof(m_unk0x124));
	m_unk0x124[0] = 0;
}

// FUNCTION: GOLDP 0x100288e0
WhiteFalcon0x140::~WhiteFalcon0x140()
{
	Destroy();
}

// FUNCTION: GOLDP 0x100288f0
void WhiteFalcon0x140::Destroy()
{
	if (m_textureFormats != NULL) {
		delete[] m_textureFormats;
		m_textureFormats = NULL;
	}

	AmberHaze0x1c* amberHaze = m_unk0x3c;
	m_countTextureFormats = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;

	while (amberHaze != NULL) {
		AmberHaze0x1c* next = amberHaze->GetNext();
		amberHaze->Clear();
		amberHaze = next;
	}

	MagentaRibbon0x20* magentaRibbon = m_unk0x38;
	while (magentaRibbon != NULL) {
		MagentaRibbon0x20* next = magentaRibbon->GetNext();
		magentaRibbon->Clear();
		magentaRibbon = next;
	}

	HypnoticNoise0x1c* hypnoticNoise = m_unk0x40;
	while (hypnoticNoise != NULL) {
		HypnoticNoise0x1c* next = hypnoticNoise->GetNext();
		hypnoticNoise->Clear();
		hypnoticNoise = next;
	}

	CinderBasin0x28* cinderBasin = m_unk0x44;
	while (cinderBasin != NULL) {
		CinderBasin0x28* next = cinderBasin->GetNext();
		cinderBasin->Clear();
		cinderBasin = next;
	}
}

// STUB: GOLDP 0x10028980
void WhiteFalcon0x140::VTable0x04()
{
	STUB(0x10028980);
}

// STUB: GOLDP 0x10028a10
void WhiteFalcon0x140::VTable0x00()
{
	STUB(0x10028a10);
}

// FUNCTION: GOLDP 0x10028a70
void WhiteFalcon0x140::FUN_10028a70(CinderBasin0x28* p_param)
{
	p_param->SetNext(m_unk0x44);
	m_unk0x44 = p_param;
}

// FUNCTION: GOLDP 0x10028a80
void WhiteFalcon0x140::FUN_10028a80(CinderBasin0x28* p_param)
{
	CinderBasin0x28* node = m_unk0x44;

	if (node != NULL) {
		if (p_param == node) {
			m_unk0x44 = node->GetNext();
			return;
		}

		CinderBasin0x28* previous = node;
		node = node->GetNext();

		while (node != NULL) {
			if (node == p_param) {
				previous->SetNext(node->GetNext());
				node->SetNext(NULL);
				return;
			}

			previous = node;
			node = node->GetNext();
		}
	}
}

// FUNCTION: GOLDP 0x10028ad0
void WhiteFalcon0x140::FUN_10028ad0(HypnoticNoise0x1c* p_param)
{
	p_param->SetNext(m_unk0x40);
	m_unk0x40 = p_param;
}

// FUNCTION: GOLDP 0x10028ae0
void WhiteFalcon0x140::FUN_10028ae0(HypnoticNoise0x1c* p_param)
{
	HypnoticNoise0x1c* node = m_unk0x40;

	if (node != NULL) {
		if (p_param == node) {
			m_unk0x40 = node->GetNext();
			return;
		}

		HypnoticNoise0x1c* previous = node;
		node = node->GetNext();

		while (node != NULL) {
			if (node == p_param) {
				previous->SetNext(node->GetNext());
				node->SetNext(NULL);
				return;
			}

			previous = node;
			node = node->GetNext();
		}
	}
}

// FUNCTION: GOLDP 0x10028b30
void WhiteFalcon0x140::FUN_10028b30(MagentaRibbon0x20* p_param)
{
	p_param->SetNext(m_unk0x38);
	m_unk0x38 = p_param;
}

// FUNCTION: GOLDP 0x10028b40
void WhiteFalcon0x140::FUN_10028b40(MagentaRibbon0x20* p_param)
{
	MagentaRibbon0x20* node = m_unk0x38;

	if (node != NULL) {
		if (p_param == node) {
			m_unk0x38 = node->GetNext();
			return;
		}

		MagentaRibbon0x20* previous = node;
		node = node->GetNext();

		while (node != NULL) {
			if (node == p_param) {
				previous->SetNext(node->GetNext());
				node->SetNext(NULL);
				return;
			}

			previous = node;
			node = node->GetNext();
		}
	}
}

// FUNCTION: GOLDP 0x10028b90
void* WhiteFalcon0x140::FUN_10028b90(const LegoChar* p_name)
{
	MagentaRibbon0x20* node = m_unk0x38;

	while (node != NULL) {
		if (node->GetNameEntries() != NULL) {
			void* value = node->GetName(p_name);
			if (value != NULL) {
				return value;
			}
		}

		node = node->GetNext();
	}

	return NULL;
}

// FUNCTION: GOLDP 0x10028bc0
void WhiteFalcon0x140::FUN_10028bc0(AmberHaze0x1c* p_param)
{
	p_param->SetNext(m_unk0x3c);
	m_unk0x3c = p_param;
}

// FUNCTION: GOLDP 0x10028bd0
void WhiteFalcon0x140::FUN_10028bd0(AmberHaze0x1c* p_param)
{
	AmberHaze0x1c* node = m_unk0x3c;

	if (node != NULL) {
		if (p_param == node) {
			m_unk0x3c = node->GetNext();
			return;
		}

		AmberHaze0x1c* previous = node;
		node = node->GetNext();

		while (node != NULL) {
			if (node == p_param) {
				previous->SetNext(node->GetNext());
				node->SetNext(NULL);
				return;
			}

			previous = node;
			node = node->GetNext();
		}
	}
}

// FUNCTION: GOLDP 0x10028c20
void* WhiteFalcon0x140::FUN_10028c20(const LegoChar* p_name)
{
	AmberHaze0x1c* node = m_unk0x3c;

	while (node != NULL) {
		if (node->GetNameEntries() != NULL) {
			void* value = node->GetName(p_name);
			if (value != NULL) {
				return value;
			}
		}

		node = node->GetNext();
	}

	return NULL;
}

// STUB: GOLDP 0x10028c50
void WhiteFalcon0x140::VTable0x0c(undefined4, undefined4, undefined4)
{
	STUB(0x10028c50);
}

// STUB: GOLDP 0x10029500
void WhiteFalcon0x140::VTable0xa4()
{
	STUB(0x10029500);
}

// STUB: GOLDP 0x10029680
void WhiteFalcon0x140::VTable0xa0()
{
	STUB(0x10029680);
}

// FUNCTION: GOLDP 0x10029840
void WhiteFalcon0x140::VTable0xa8(undefined4 p_param1, undefined4 p_param2, undefined4 p_param3)
{
	VTable0x94(p_param1);
}

// FUNCTION: GOLDP 0x10029850
void WhiteFalcon0x140::SetAlphaOverride(undefined4 p_alpha, undefined4 p_flags)
{
	m_unk0x04 |= c_flagBit14;
	m_unk0x0a = p_alpha;
	m_unk0x08 = p_flags;
}

// FUNCTION: GOLDP 0x10029870
void WhiteFalcon0x140::ClearAlphaOverride()
{
	m_unk0x04 &= ~c_flagBit14;
}

// FUNCTION: GOLDP 0x10029880
void WhiteFalcon0x140::VTable0xc0(undefined4* p_param)
{
	m_unk0x118 = *p_param;
	m_unk0x04 |= c_flagBit19;
}

// FUNCTION: GOLDP 0x100298a0
void WhiteFalcon0x140::VTable0xc4()
{
	m_unk0x04 &= ~c_flagBit19;
}

// FUNCTION: GOLDP 0x100298b0
void WhiteFalcon0x140::VTable0x28()
{
	m_unk0x04 &= ~c_flagBit15;
	m_unk0x11c = 0;
	m_unk0x120 = 0;
	m_unk0x124[0] = 0;
}

// FUNCTION: GOLDP 0x100298d0
void WhiteFalcon0x140::VTable0x2c(undefined4 p_param)
{
	m_unk0x04 |= c_flagBit15;
	m_unk0x120 = p_param;
}

// FUNCTION: GOLDP 0x100298f0
void WhiteFalcon0x140::VTable0x30(undefined4 p_param)
{
	if (m_unk0x11c < 7) {
		m_unk0x04 |= c_flagBit15;
		m_unk0x124[m_unk0x11c] = p_param;
		m_unk0x11c++;
	}
}

// FUNCTION: GOLDP 0x10029930
void WhiteFalcon0x140::VTable0x44()
{
	m_unk0x04 |= c_flagBit18;
}

// FUNCTION: GOLDP 0x10029940
void WhiteFalcon0x140::VTable0x48()
{
	m_unk0x04 &= ~c_flagBit18;
}

// FUNCTION: GOLDP 0x10029960
void WhiteFalcon0x140::VTable0x58(undefined4 p_param1, undefined4 p_param2)
{
	VTable0x54(p_param2);
}

// FUNCTION: GOLDP 0x10029970
void WhiteFalcon0x140::VTable0x24()
{
	m_unk0x0c = 0;
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void WhiteFalcon0x140::VTable0x38()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void WhiteFalcon0x140::VTable0x40()
{
	// empty
}

// FUNCTION: GOLDP 0x10029950 FOLDED
SlatePeak0x58* WhiteFalcon0x140::VTable0x4c(undefined2, undefined2)
{
	return NULL;
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void WhiteFalcon0x140::VTable0x50(undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void WhiteFalcon0x140::VTable0x60()
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void WhiteFalcon0x140::VTable0x88(undefined4, undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void WhiteFalcon0x140::VTable0x8c(undefined4, undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void WhiteFalcon0x140::VTable0x98(undefined4, undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void WhiteFalcon0x140::VTable0x9c(undefined4, undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void WhiteFalcon0x140::VTable0x34(LegoS32 p_unk0x04, const LegoFloat* p_unk0x08)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void WhiteFalcon0x140::VTable0xac(undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void WhiteFalcon0x140::VTable0xb0(undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void WhiteFalcon0x140::VTable0x3c(undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void WhiteFalcon0x140::VTable0xc8()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void WhiteFalcon0x140::VTable0xcc()
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void WhiteFalcon0x140::VTable0xec(undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void WhiteFalcon0x140::VTable0xf4()
{
	// empty
}

// STUB: GOLDP 0x100016f0 FOLDED
LegoBool32 WhiteFalcon0x140::VTable0x110() const
{
	MATCHING(0x100016f0);
	return FALSE;
}
