extern int emu_display;
extern int show_sysvars;
extern int show_memmap;
extern int show_status;
extern int show_status2;
//extern int memmap_bankno;

extern void update_tape_gui();
extern void update_tape_gui_speed(int);
extern void update_fps_counter(int);
extern void gui_error(char *);
extern void update_gui_mtype(int);
extern void init_gui();
extern void gui_loop_more();
extern void init_sound();
extern void post_init_gui();

extern void update_sysvars();
extern void update_memmap();
extern void update_status();
extern void _chdir(char *);

extern void update_gui_speed(int);
extern void update_sysvar();
extern int show_tapemon;
extern void update_tape_monitor();
extern int show_memscan;
extern void update_memscan();
extern void gui_loop();
extern void gui_end();
extern void set_memmap_bankno( int);
extern void set_show_memmap(int);
extern void set_show_status(int);
extern void set_show_sysvars( int);
extern void set_display();
extern void set_SoundEnable();
extern void update_sound();



extern void update_disksize_gui();
extern void update_disk_gui();


