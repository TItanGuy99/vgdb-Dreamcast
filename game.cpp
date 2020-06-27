/*Code and engine made by Titan Game Studios 2016/2020 coded by Luiz Nai.*/
#include "game.h"

SDL_Rect baseclass::coord; //we have to actually reserve memory for the static SDL_Rect from the baseclass
int save_clock;
 
game::game()    //constructor
{	
	//init kos
    vid_init(DM_GENERIC_FIRST, PM_RGB565);
    pvr_init_defaults();
	
	SDL_Init(SDL_INIT_JOYSTICK);
	
	snd_stream_init();
			
	screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,24,SDL_FULLSCREEN);
	PVR_SET(PVR_SCALER_CFG, 0x400);
	
	SDL_ShowCursor(SDL_DISABLE);
	SDL_JoystickEventState(SDL_ENABLE);
	
	joystick = SDL_JoystickOpen(0);
	buttonCount = SDL_JoystickNumButtons(joystick);
		
	SDL_Delay(200);
	
	m_screen = load_image("rd/images/menu/menu.bmp");
	jaguar = load_image("rd/images/menu/jaguar.bmp");
	v_letter = load_image("rd/images/menu/imagev.bmp");
	g_letter = load_image("rd/images/menu/imageg.bmp");
	d_letter = load_image("rd/images/menu/imaged.bmp");
	b_letter = load_image("rd/images/menu/imageb.bmp");
	vgdb_logo = load_image("rd/images/menu/vgdblogo.bmp");
	showjaguar = false;
		
	baseclass::coord.x = 0;
	baseclass::coord.y = 0;
	camera.x=0;
	camera.y=0;
	counter = 0;
	total_counter = 20;
	half_total = total_counter/2;

	v_rect.x = -2;
	v_rect.y = -20;
	v_rect.w = -74;
	v_rect.h = -92;

	g_rect.x = -82;
	g_rect.y = -40;
	g_rect.w = -74;
	g_rect.h = -92;

	d_rect.x =-163;
	d_rect.y = -20;
	d_rect.w = -74;
	d_rect.h = -92;

	b_rect.x =-242;
	b_rect.y = -40;
	b_rect.w = -74;
	b_rect.h = -92;

	logo_rect.x = -4;
	logo_rect.y = -200;
	logo_rect.w = -307;
	logo_rect.h = -20;

	///////////////
	baseclass::coord.w=SCREEN_WIDTH;
	///////////////
	camera.w=SCREEN_WIDTH;
	baseclass::coord.h=SCREEN_HEIGHT;
	camera.h=SCREEN_HEIGHT;
}

///// Destroy all the variables in the memory for the game.
game::~game()
{
	SDL_FreeSurface(m_screen);
	SDL_FreeSurface(jaguar);	
	SDL_FreeSurface(v_letter);	
	SDL_FreeSurface(g_letter);	
	SDL_FreeSurface(d_letter);	
	SDL_FreeSurface(b_letter);	
	SDL_FreeSurface(vgdb_logo);	
	SDL_Quit();
	pvr_shutdown();
}

///////Function to load the images
SDL_Surface* game::load_image(const char* filename)     //it will load an image
{
        SDL_Surface* tmp=SDL_LoadBMP(filename); //load the BMP to a tmp variable
        SDL_Surface* tmp2=SDL_DisplayFormat(tmp);       //change it to the format of the screen
        SDL_FreeSurface(tmp);   //free the tmp, we don't need it anymore
        return tmp2;    //return
}

////Function to handle all the Joystick/Keyboard events
void game::handleEvents()
{
	SDL_Event event;
		
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{			
            case SDL_JOYBUTTONDOWN:
			    switch(event.jbutton.button)
				{				
					case 4:
						showjaguar = true;
					break;						
				}
			break;

            case SDL_JOYBUTTONUP:
			    switch(event.jbutton.button)
				{				
					case 4:
						showjaguar = false;
					break;						
				}
			break;

            default:

            break;
		}
	}
}

void game::animation() {
	counter++;

	if(counter <= half_total)
	{
		v_rect.y++;
		g_rect.y--; 
		d_rect.y++; 
		b_rect.y--; 
	}
	else
	{
		v_rect.y--;
		g_rect.y++; 
		d_rect.y--; 
		b_rect.y++; 		
	}

	if(counter==total_counter) {
		counter=0;
	}
}

///// Function to start the game
void game::start()
{	
	bool runing=true;
	static pvr_poly_hdr_t hdr[2];
	pvr_poly_cxt_t cxt;
	vmu();
	Uint32 start;
	cdrom_cdda_play(1, 1, 10, CDDA_TRACKS);
	while(running)
	{
		start=SDL_GetTicks();
		handleEvents();
		SDL_FillRect(screen,NULL, 0x000000); 
		SDL_BlitSurface(m_screen,&camera,screen,NULL);
		SDL_BlitSurface(v_letter,&v_rect,screen,NULL);
		SDL_BlitSurface(g_letter,&g_rect,screen,NULL);
		SDL_BlitSurface(d_letter,&d_rect,screen,NULL);
		SDL_BlitSurface(b_letter,&b_rect,screen,NULL);
		SDL_BlitSurface(vgdb_logo,&logo_rect,screen,NULL);


		if(showjaguar) {
			SDL_BlitSurface(jaguar,&camera,screen,NULL);
		}
		else {
			animation();
		}

		SDL_UpdateRect(screen, 0, 0, 0, 0);
			
		save_clock=SDL_GetTicks()-start;
			
		if(SDL_GetTicks()-start<=20)
		{
			SDL_Delay(10);
		}
		else
		{
			SDL_Delay(5);
		}
	}
}