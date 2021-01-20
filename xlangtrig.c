#include <stdio.h>
#include <stdlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>

int main(int argc, char **argv)
{
  XEvent e;
  Display *d;

  if (!(d = XOpenDisplay(NULL))) {
    fprintf(stderr, "cannot open display\n");
    return 1;
  }

  XKeysymToKeycode(d, XK_F1);

  int xkbEventType;
  XkbQueryExtension(d, 0, &xkbEventType, 0, 0, 0);
  XkbSelectEvents(d, XkbUseCoreKbd, XkbAllEventsMask, XkbAllEventsMask);

  XSync(d, False);

  int origLang = -1;

  while (1) {
    XNextEvent(d, &e);

    if (e.type == xkbEventType) {
      XkbEvent* xkbEvent = (XkbEvent*) &e;

      if (xkbEvent->any.xkb_type == XkbStateNotify) {
        int lang = xkbEvent->state.group;

        if (lang == origLang) {
          continue;
        }

        origLang = lang;

        if (lang == 0) {
          if (system("/home/danil/go/bin/yq write --inplace /home/danil/.config/alacritty/alacritty.yml 'colors.cursor.cursor' '#ff0000'") != 0) {
            fprintf(stderr, "language 0 error\n");
            return 1;
          }
        } else {
          if (system("/home/danil/go/bin/yq write --inplace /home/danil/.config/alacritty/alacritty.yml 'colors.cursor.cursor' '#ffff00'") != 0) {
            fprintf(stderr, "language 1 error \n");
            return 1;
          }
        }
      }
    }
  }

  return(0);
}
