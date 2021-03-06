//Directory functions


#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

typedef struct {
    unsigned short twosecs : 5; /* seconds / 2 */
    unsigned short minutes : 6;
    unsigned short hours : 5;
}ftime_t;

typedef struct {
    unsigned short day : 5;
    unsigned short month : 4;
    unsigned short year : 7;
}fdate_t;

void get_directory(char *pathext,char *listing,unsigned int highlight,char *name)
{
    DIR *dirp;
    struct dirent *direntp;
   
    ftime_t *f_time;
    fdate_t *f_date;
   
    char lbl[200],lbl2[200];
    char list_dir[256];
    int noof_entries_horiz,noof_entries_vert = 0;
        int noof_entries = 0;
 
 //   sprintf(list_dir,"%s/*.%s",pathext,pathext);
//  sprintf(list_dir,"./%s/*.%s",pathext);
sprintf(list_dir,"./%s",pathext);

    sprintf(listing,"Directory:%s\n",list_dir);

    dirp = opendir( list_dir );
    if( dirp != NULL )
    {
        noof_entries_horiz = 0;
        for(;;)
        {
            direntp = readdir( dirp );
            if(direntp == NULL)
                break;

                        if(noof_entries == highlight)
                        {
                            sprintf(lbl,"\a1\f7");
                            sprintf(lbl2,"%s",direntp->d_name);
                            strcat(lbl,lbl2);
                            sprintf(lbl2,"\a0\f2   ");
                            strcat(lbl,lbl2);
                            strcpy(name,direntp->d_name);
                        }
                        else
                            sprintf(lbl,"%s   ",direntp->d_name);
            
                        noof_entries_horiz++;
            if(noof_entries_horiz > 1)
            {
                strcat(listing,"\n");    
                noof_entries_horiz = 0;
                //noof_entries_vert++;
                //if(noof_entries_vert > 15)break;
            }
            noof_entries ++;
            strcat(listing,lbl);    
        }
        closedir(dirp);
     }
    sprintf(lbl,"\n\n\a1\f4Filename: ");
    strcat(lbl,name);
    strcat(listing,lbl);    
    strcat(listing,"\0");
    sprintf(list_dir,"%s/%s",pathext,name);
    strcpy(name,list_dir);

}

