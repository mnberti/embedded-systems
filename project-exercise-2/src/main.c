//
/*
Steve Combs remix
http://freemusicarchive.org/music/download/9bcc64b677b3746b62c47a7584435304fd8e156d

Free sound effects
http://soundscrate.com/scifi.html
explosion2

http://www.freesfx.co.uk
Laser
*/

#include <time.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
// #include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>
#include <stdio.h>

#define ScreenWidth 800
#define ScreenHeight 600
#define rectdim 40
#define appledim 21

#define RESERVED_SAMPLES 16

bool Overlap(int p2x, int p2y, int p2dim);
char msgbuf[80]; // dialog message text buffer

float moveSpeed = 5;
int bar;
bool foo;
int x = 0, y = 0;
int score = -1;

int appleposx;
int appleposy;
bool eaten = false;
int start = 1;
int textfor = 700;
int life = 5;
char LiveString[30];

time_t rawtime;
struct tm *info;
char buffer[80];

int evilposx = ScreenWidth + 1, evilposy = ScreenHeight + 1, evildone = 0;
int evilposx1 = ScreenWidth + 1, evilposy1 = ScreenHeight + 1, evildone1 = 0;
int evilposx2 = ScreenWidth + 1, evilposy2 = ScreenHeight + 1, evildone2 = 0;
int evilposx3 = ScreenWidth + 1, evilposy3 = ScreenHeight + 1, evildone3 = 0;
int evilposx4 = ScreenWidth + 1, evilposy4 = ScreenHeight + 1, evildone4 = 0;
int evilposx5 = ScreenWidth + 1, evilposy5 = ScreenHeight + 1, evildone5 = 0;
int evilposx6 = ScreenWidth + 1, evilposy6 = ScreenHeight + 1, evildone6 = 0;

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};
int dir = NONE;

void level2()
{
}

int rand_between(const int min, const int max)
{
	int range = max - min;
	return rand() % range + min;
}

int applepos()
{
	appleposx = rand_between(0, ScreenWidth - appledim);
	appleposy = rand_between(0, ScreenHeight - appledim);
	score++;
	return 0;
}

int evilcubepos()
{
	evilposx = rand_between(0, ScreenWidth - appledim);
	evilposy = rand_between(0, ScreenHeight - appledim);
	evildone++;
	return 0;
}

int evilcubepos1()
{
	evilposx1 = rand_between(0, ScreenWidth - appledim);
	evilposy1 = rand_between(0, ScreenHeight - appledim);
	evildone1++;
	return 0;
}

int evilcubepos2()
{
	evilposx2 = rand_between(0, ScreenWidth - appledim);
	evilposy2 = rand_between(0, ScreenHeight - appledim);
	evildone2++;
	return 0;
}

int evilcubepos3()
{
	evilposx3 = rand_between(0, ScreenWidth - appledim);
	evilposy3 = rand_between(0, ScreenHeight - appledim);
	evildone3++;
	return 0;
}

int evilcubepos4()
{
	evilposx4 = rand_between(0, ScreenWidth - appledim);
	evilposy4 = rand_between(0, ScreenHeight - appledim);
	evildone4++;
	return 0;
}

int evilcubepos5()
{
	evilposx5 = rand_between(0, ScreenWidth - appledim);
	evilposy5 = rand_between(0, ScreenHeight - appledim);
	evildone5++;
	return 0;
}

int evilcubepos6()
{
	evilposx6 = rand_between(0, ScreenWidth - appledim);
	evilposy6 = rand_between(0, ScreenHeight - appledim);
	evildone6++;
	return 0;
}

void gameover()
{

	foo = true;
	moveSpeed = 5;
	bar = start;
	score = 0;
	evilposx = ScreenWidth + 1, evilposy = ScreenHeight + 1, evildone = 0;
	evilposx1 = ScreenWidth + 1, evilposy1 = ScreenHeight + 1, evildone1 = 0;
	evilposx2 = ScreenWidth + 1, evilposy2 = ScreenHeight + 1, evildone2 = 0;
	evilposx3 = ScreenWidth + 1, evilposy3 = ScreenHeight + 1, evildone3 = 0;
	evilposx4 = ScreenWidth + 1, evilposy4 = ScreenHeight + 1, evildone4 = 0;
	evilposx5 = ScreenWidth + 1, evilposy5 = ScreenHeight + 1, evildone5 = 0;
	evilposx6 = ScreenWidth + 1, evilposy6 = ScreenHeight + 1, evildone6 = 0;
	x = ScreenWidth, y = ScreenHeight;
	dir = NONE;
}

int main(void)
{

	const float FPS = 60.0;
	const char *font_file = "data/DejaVuSans.ttf";

	time(&rawtime);

	info = localtime(&rawtime);

	strftime(buffer, 80, "Exit: Esc - %x - %I:%M%p", info);

	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Could Not init Allegro5", NULL, 0);
		return -1;
	}

	// Window
	ALLEGRO_SAMPLE *BackMusic = {NULL};
	ALLEGRO_SAMPLE *Explosion = {NULL};
	ALLEGRO_SAMPLE *LaserRay = {NULL};
	al_set_new_display_flags(ALLEGRO_NOFRAME);
	ALLEGRO_DISPLAY *display;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *event_queue;

	// setup
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();

	display = al_create_display(ScreenWidth, ScreenHeight);

	ALLEGRO_FONT *font = al_load_font(font_file, 36, 0);
	ALLEGRO_FONT *fontsmall = al_load_font(font_file, 20, 0);

	// ALLEGRO_KEYBOARD_STATE keyState;
	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	srand(time(NULL));

	al_init_acodec_addon();
	if (!al_install_audio())
	{
		// abort_example("Could not init sound!\n");
		al_show_native_message_box(display, "Warning", NULL, "Could not init sound!", NULL, 0);
		return -1;
	}

	if (!al_reserve_samples(RESERVED_SAMPLES))
	{
		// abort_example("Could not set up voice and mixer.\n");
		al_show_native_message_box(display, "Warning", NULL, "Could not set up voice and mixer.\n", NULL, 0);
		return -1;
	}

	// memset(BackMusic, 0, sizeof(BackMusic));
	// for (i = 0; i < argc && i < MAX_SAMPLE_DATA; i++) {
	const char *ThemeName = "data/SteveCombsRemix.ogg";
	const char *ExploName = "data/Explosion2.ogg";
	const char *LaserName = "data/laser_ray.ogg";

	/* Load the entire sound file from disk. */
	BackMusic = al_load_sample(ThemeName);
	Explosion = al_load_sample(ExploName);
	LaserRay = al_load_sample(LaserName);

	if (!BackMusic)
	{
		// printf("Could not load sample from '%s'!\n", Themename);
		sprintf(msgbuf, "Could not load sample from '%s'!\n", ThemeName);
		al_show_native_message_box(display, NULL, NULL, msgbuf, NULL, 0);
	}

	if (!al_play_sample(BackMusic, 1.0, 0.5, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL))
	{
		al_show_native_message_box(display, NULL, NULL,
								   "al_play_sample_data failed, perhaps too many sounds\n", NULL, 0);
	}

	// actual code for game.

	bool done = false, draw = true, eaten = false;

	applepos();

	// int state = NULL;

	/*Can't Declare Variables When Timer is Running So Placed Just Before Game Loop is Initianlized Rather then in the Setup*/
	al_start_timer(timer);
	while (!done)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}

		/*Update*/
		if (events.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (events.keyboard.keycode)
			{

			case ALLEGRO_KEY_UP:
				dir = UP;
				break;

			case ALLEGRO_KEY_LEFT:
				dir = LEFT;
				break;

			case ALLEGRO_KEY_RIGHT:
				dir = RIGHT;
				break;

			case ALLEGRO_KEY_DOWN:
				dir = DOWN;
				break;

			case ALLEGRO_KEY_ENTER:
				if (foo)
				{
					foo = false;
					applepos();
					x = ScreenWidth / 2 - rectdim / 2, y = ScreenHeight / 2 - rectdim / 2;
					life = 5;
				}
				break;
			}
		}

		if (!foo)
		{
			if (events.type == ALLEGRO_EVENT_TIMER)
			{
				switch (dir)
				{

				case LEFT:
					x -= moveSpeed;
					break;

				case RIGHT:
					x += moveSpeed;
					break;

				case UP:
					y -= moveSpeed;
					break;

				case DOWN:
					y += moveSpeed;
					break;
				}
				draw = true;
			}
		}

		// stop at edge
		if (x >= ScreenWidth - rectdim)
		{
			x = ScreenWidth - rectdim;
		}
		if (x <= 0)
		{
			x = 0;
		}
		if (y >= ScreenHeight - rectdim)
		{
			y = ScreenHeight - rectdim;
		}
		if (y <= 0)
		{
			y = 0;
		}

		// eat the apple
		if (Overlap(appleposx, appleposy, appledim))
		{
			eaten = true;
			al_play_sample(LaserRay, 1.0, 0.5, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		//
		// red kills you.
		if (Overlap(evilposx, evilposy, appledim))
		{
			life--;
			evilcubepos();
			al_play_sample(Explosion, 1.0, 0.5, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}

		if (Overlap(evilposx1, evilposy1, appledim))
		{
			life--;
			evilcubepos1();
			al_play_sample(Explosion, 1.0, 0.5, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		if (Overlap(evilposx2, evilposy2, appledim))
		{
			life--;
			evilcubepos2();
			al_play_sample(Explosion, 1.0, 0.5, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}

		if (Overlap(evilposx3, evilposy3, appledim))
		{
			life--;
			evilcubepos3();
			al_play_sample(Explosion, 1.0, 0.5, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}

		if (Overlap(evilposx4, evilposy4, appledim))
		{
			life--;
			evilcubepos4();
			al_play_sample(Explosion, 1.0, 0.5, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}

		if (Overlap(evilposx5, evilposy5, appledim))
		{
			life--;
			evilcubepos5();
			al_play_sample(Explosion, 1.0, 0.5, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}

		if (Overlap(evilposx6, evilposy6, appledim))
		{
			life--;
			evilcubepos6();
			al_play_sample(Explosion, 1.0, 0.5, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}

		if (life < 1)
		{
			gameover();
		}
		if (score >= 20)
		{
			// level 2();
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// draw mode

		if (draw)
		{
			draw = false;
			// Apple
			if (eaten == false)
			{
				al_draw_filled_rectangle(appleposx, appleposy, appleposx + appledim, appleposy + appledim, al_map_rgb(0, 255, 0));
			}
			else
			{
				applepos();
				eaten = false;
			}

			if (score > 0)
			{
				if (evildone == 0)
				{
					evilcubepos();
				}
			}

			if (score > 1)
			{
				if (evildone1 == 0)
				{
					evilcubepos1();
					moveSpeed += 0.5f;
				}
			}

			if (score > 2)
			{
				if (evildone2 == 0)
				{
					evilcubepos2();
					moveSpeed += 0.5f;
				}
			}

			if (score > 3)
			{
				if (evildone3 == 0)
				{
					evilcubepos3();
					moveSpeed += 0.5f;
				}
			}

			if (score > 4)
			{
				if (evildone4 == 0)
				{
					evilcubepos4();
					moveSpeed += 0.5f;
				}
			}

			if (score > 5)
			{
				if (evildone5 == 0)
				{
					evilcubepos5();
					moveSpeed += 0.5f;
				}
			}

			if (score > 6)
			{
				if (evildone6 == 0)
				{
					evilcubepos6();
					moveSpeed += 0.5f;
				}
			}

			// draw body parts

			// draw evil cubes
			al_draw_filled_rectangle(evilposx, evilposy, evilposx + appledim, evilposy + appledim, al_map_rgb(255, 0, 0));
			al_draw_filled_rectangle(evilposx1, evilposy1, evilposx1 + appledim, evilposy1 + appledim, al_map_rgb(255, 0, 0));
			al_draw_filled_rectangle(evilposx2, evilposy2, evilposx2 + appledim, evilposy2 + appledim, al_map_rgb(255, 0, 0));
			al_draw_filled_rectangle(evilposx3, evilposy3, evilposx3 + appledim, evilposy3 + appledim, al_map_rgb(255, 0, 0));
			al_draw_filled_rectangle(evilposx4, evilposy4, evilposx4 + appledim, evilposy4 + appledim, al_map_rgb(255, 0, 0));
			al_draw_filled_rectangle(evilposx5, evilposy5, evilposx5 + appledim, evilposy5 + appledim, al_map_rgb(255, 0, 0));
			al_draw_filled_rectangle(evilposx6, evilposy6, evilposx6 + appledim, evilposy6 + appledim, al_map_rgb(255, 0, 0));

			// draw snake parts

			al_draw_filled_rectangle(x, y, x + rectdim, y + rectdim, al_map_rgb(0, 0, 255));

			// draw all text

			al_draw_text(fontsmall, al_map_rgb(255, 255, 255), 10, 10, 0, buffer);

			if (start <= 200)
			{
				al_draw_text(font, al_map_rgb(255, 255, 255), ScreenWidth / 2, ScreenHeight / 2, ALLEGRO_ALIGN_CENTER, "Welcome to Squarenoids!");
				start++;
			}
			if (start > 200 && start < 400)
			{
				al_draw_text(font, al_map_rgb(255, 255, 255), ScreenWidth / 2, ScreenHeight / 2, ALLEGRO_ALIGN_CENTER, "Use the arrow keys to move");
				al_draw_text(font, al_map_rgb(255, 255, 255), ScreenWidth / 2, (ScreenHeight / 2) + 50, ALLEGRO_ALIGN_CENTER, "Escape to Exit");
				start++;
			}
			if (start >= 400 && start < textfor)
			{
				al_draw_text(font, al_map_rgb(255, 255, 255), ScreenWidth / 2, ScreenHeight / 2, ALLEGRO_ALIGN_CENTER, "Collect all the Green Squares");
				al_draw_text(font, al_map_rgb(255, 255, 255), ScreenWidth / 2, (ScreenHeight / 2) + 50, ALLEGRO_ALIGN_CENTER, "and Avoid the Red ones. ");
				start++;
			}

			if (foo)
			{
				al_draw_text(font, al_map_rgb(255, 255, 255), ScreenWidth / 2, (ScreenHeight / 2) + 50, ALLEGRO_ALIGN_CENTER, "Game Over, To Try Again Press Enter");

				dir = NONE;
			}

			if (life == 5)
			{
				strcpy(LiveString, "Lives: 5 ");
				al_draw_text(font, al_map_rgb(255, 255, 255), ScreenWidth - 50, 0, ALLEGRO_ALIGN_RIGHT, LiveString);
			}
			if (life == 4)
			{
				strcpy(LiveString, "Lives: 4 ");
				al_draw_text(font, al_map_rgb(255, 255, 255), ScreenWidth - 50, 0, ALLEGRO_ALIGN_RIGHT, LiveString);
			}
			if (life == 3)
			{
				strcpy(LiveString, "Lives: 3 ");
				al_draw_text(font, al_map_rgb(255, 255, 255), ScreenWidth - 50, 0, ALLEGRO_ALIGN_RIGHT, LiveString);
			}
			if (life == 2)
			{
				strcpy(LiveString, "Lives: 2 ");
				al_draw_text(font, al_map_rgb(255, 255, 255), ScreenWidth - 50, 0, ALLEGRO_ALIGN_RIGHT, LiveString);
			}
			if (life == 1)
			{
				strcpy(LiveString, "Lives: 1 ");
				al_draw_text(font, al_map_rgb(255, 255, 255), ScreenWidth - 50, 0, ALLEGRO_ALIGN_RIGHT, LiveString);
			}

			// other stuff
			al_flip_display();
			al_clear_to_color(al_map_rgb(100, 100, 100));
		}
	}

	// end code.

	al_uninstall_audio();
	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return 0;
}

// Returns true if two rectangles (l1, r1) and (l2, r2) overlap
// http://www.geeksforgeeks.org/find-two-rectangles-overlap/
/*
	  l2+------------+
		|            |
l1      |            |
+------------+       |
|       |    |       |
|       +----|-------+
|            |       r2
+------------+
			 r1
			 */
bool Overlap(int p2x, int p2y, int p2dim)
{
	int l1x, l1y, r1x, r1y, l2x, l2y, r2x, r2y;
	// map the coordinates  x,y, rectdim are global my coords
	l1x = x;
	l1y = y + rectdim;
	r1x = x + rectdim;
	r1y = y;
	l2x = p2x;
	l2y = p2y + p2dim;
	r2x = p2x + p2dim;
	r2y = p2y;
	//
	// If one rectangle is on left side of other
	if (l1x > r2x || l2x > r1x)
		return false;

	// If one rectangle is above other
	if (l1y < r2y || l2y < r1y)
		return false;

	return true;
}
