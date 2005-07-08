/*
 * This source code is a part of coLinux source package.
 *
 * Nuno Lucas <lucas@xpto.ath.cx> 2005 (c)
 *
 * The code is licensed under the GPL. See the COPYING file at
 * the root directory.
 *
 */
#ifndef COLINUX_USER_CONSOLE_SCREEN_COCON_H
#define COLINUX_USER_CONSOLE_SCREEN_COCON_H

#include "screen.h"
extern "C" {
	#include <linux/cooperative_video.h>
}


/* ----------------------------------------------------------------------- */
/*
 * Screen rendering engine for the cocon driver.
 *
 * Implementation of the screen_render abstract class for the cocon driver.
 */
class screen_cocon_render : public screen_render
{
public:
     screen_cocon_render( cocon_video_mem_info * info );
    ~screen_cocon_render( );
    unsigned long id() const            { return info_.header.magic; }
    int w() const                       { return w_; }
    int h() const                       { return h_; }
    void reset( );
    void draw( int x, int y );

private:
    int c2x( int col ) const        { return col*fw_; }
    int r2y( int row ) const        { return row*fh_; }
    __u32 color( int idx ) const    { return palette_[idx]; }
    __u32& pixel( int x, int y )    { return fb_[y*w_ + x]; }

    void render_char( int row, int col, __u16 charattr );
    void render_str( int row, int col, __u16 * strattr, int len );

private:
    cocon_video_mem_info    &   info_;
    __u8                    *   vram_;
    __u32                   *   fb_;
    unsigned			w_, h_;
    unsigned			fw_, fh_;
    unsigned			cur_h_;
    __u8                    *   font_data_;
    __u16                   *   scr_base_;
    __u32                   *   palette_;
};


#endif // COLINUX_USER_CONSOLE_SCREEN_COCON_H
