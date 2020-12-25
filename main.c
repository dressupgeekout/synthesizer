/*
 * main.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <fluidsynth.h>

int
main(int argc, char *argv[])
{
	printf("*** SYNTHESIZER ***\n");

	SDL_Init(SDL_INIT_AUDIO|SDL_INIT_EVENTS|SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER);
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_CreateWindowAndRenderer(1280, 720, 0, &win, &renderer);
	SDL_SetWindowTitle(win, "Synthesizer");

	SDL_GameController *controller = NULL;
	if (SDL_NumJoysticks() > 0) {
		controller = SDL_GameControllerOpen(0);
		printf("Found controller: %s\n", SDL_GameControllerNameForIndex(0));
	}

	fluid_settings_t *settings;
	fluid_synth_t *synth;
	fluid_audio_driver_t *driver;
	int soundfont;

	settings = new_fluid_settings();
	//fluid_settings_setstr(settings, "audio.driver", "dsound");
	fluid_settings_setstr(settings, "audio.driver", "sdl2");

	synth = new_fluid_synth(settings);
	driver = new_fluid_audio_driver(settings, synth);
	soundfont = fluid_synth_sfload(synth, "../data/GeneralUser_GS_v1.471.sf2", 1);
	//fluid_synth_set_reverb_on(synth, true);
	//fluid_synth_set_reverb_level(synth, 1.0);
	//fluid_synth_set_reverb_roomsize(synth, 1.0);

	int presetnum = 0;

	bool done = false;
	SDL_Event event;

	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				{
					printf("KEYDOWN\n");
					int font_id, bank_num, __presetnum;

					if (event.key.keysym.sym == SDLK_UP) {
						fluid_synth_get_program(synth, 0, &font_id, &bank_num, &__presetnum);
						fluid_synth_program_select(synth, 0, font_id, bank_num, ++presetnum);
					}

					if (event.key.keysym.sym == SDLK_DOWN) {
						fluid_synth_get_program(synth, 0, &font_id, &bank_num, &__presetnum);
						fluid_synth_program_select(synth, 0, font_id, bank_num, --presetnum);
					}

					printf(">> INSTRUMENT #%d\n", presetnum);

					if (event.key.keysym.sym == SDLK_ESCAPE) {
						done = true;
					}
				}
				break;
			case SDL_JOYBUTTONDOWN:
				{
					printf("JOYBUTTONDOWN\n");
					int note = 50 + event.jbutton.button;
					fluid_synth_noteon(synth, 0, note, 127);
				}
				break;
			case SDL_JOYBUTTONUP:
				{
					printf("JOYBUTTONDOWN\n");
					int note = 50 + event.jbutton.button;
					fluid_synth_noteoff(synth, 0, note);
				}
				break;
			case SDL_JOYAXISMOTION:
				{
					if (event.jaxis.axis == 0) {
						printf("%d\n", event.jaxis.value);
						int value = 8192 + (event.jaxis.value/10);
						fluid_synth_pitch_bend(synth, 0, value);
					}
				}
				break;
			case SDL_QUIT:
				{
					done = true;
				}
				break;
			default:
				; /* OK */
			}
		}

		/* LOVE2D does this to save *lots* of CPU. */
		SDL_Delay(1);
	}

	printf("Shutting down fluidsynth...\n");
	delete_fluid_audio_driver(driver);
	delete_fluid_synth(synth);
	delete_fluid_settings(settings);

	printf("Shutting down SDL...\n");
	SDL_GameControllerClose(controller);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return EXIT_SUCCESS;
}
