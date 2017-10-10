
#include "3ds.hpp"


struct RGBLedPattern
{
	u8 delay;
	u8 smooth;
	u8 loop_delay;
	u8 unknown1;	
    u8 r[32];
    u8 g[32];
    u8 b[32];
};

struct LED_color
{
	u8 r;
	u8 g;
	u8 b;
	LED_color(u8 r1, u8 g1, u8 b1) {
		r = r1;
		g = g1;
		b = b1;
	}
};

enum class LED_PatType
{
	CONSTANT = 0, // Constant
	DESCENDENT = 1, // linear down
	ASCENDENT = 2, // linear up
	WAVE_ASC = 3, // sine wave up
	WAVE_DESC = 4, // sine wave down
};

class LED {
	private:
		static Handle ptmsysmHandle = 0;
		static bool SecureLock = false;
		static Result Init();
		static Result Play(RGBLedPattern pattern);
	public:
		// Returns true if pattern is playing, false otherwise.
		static bool IsPatternPlaying();
		// Plays a generated pattern, returns true if played successfully.
		static bool PlayLEDPattern(RGBLedPattern pattern);
		// Stops any playing pattern, returns true if stopped successfully.
		static bool StopLEDPattern();
		// Generates a Led Pattern, only one led pattern can be played at the same.
		static RGBLedPattern GeneratePattern(LED_Color color, LED_PatType type, float delay_time, float loop_delay, u8 smooth = 0, float r_shift = 0, float g_shift = 0, float b_shift = 0);
};


/* Example

Since the time is stored in one byte, the minimum amount of time is 1/16 seconds.

Infinite delay time (only the first sample is played): delay_time = 0 seconds
loop only once: loop_delay > 16 seconds
*/