/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:51:36 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/22 09:00:15 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H
/////////DISPLAY SIZE///////
# define WINX 1920	
# define WINY 1080

# define OPEN_FAILURE -1
# define FAILURE 1
# define SUCCESS 0

# define ANGLE 0.523598776
# define STEP 1
# define OFFSET 500

/////////KEY HOOK///////////
# define KEY_ESC         65307
# define KEY_W           119
# define KEY_A           97
# define KEY_S           115
# define KEY_D           100
# define KEY_Q           113
# define KEY_E           101
# define KEY_C           99
# define KEY_N           110
# define KEY_UP          65362
# define KEY_DOWN        65364
# define KEY_LEFT        65361
# define KEY_RIGHT       65363
# define KEY_PLUS        61
# define KEY_MINUS       45
# define KEY_1           49
# define KEY_2           50
# define KEY_3           51
# define KEY_4           52
# define KEY_5           53
# define KEY_6           54
# define KEY_7           55
# define KEY_8           56
# define KEY_9           57
# define KEY_0           48
# define KEY_SPACE       32
# define KEY_SHIFT       65505
# define KEY_CTRL        65507
# define KEY_ALT         65513
# define KEY_PLUS 61
# define KEY_MINUS 45
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
/////////COLORS//////////////
# define BASE_COLOR 0xffffff
# define BLACK       0x000000
# define WHITE       0xFFFFFF
# define RED         0xFF0000
# define GREEN       0x00FF00
# define BLUE        0x0000FF
# define YELLOW      0xFFFF00
# define CYAN        0x00FFFF
# define MAGENTA     0xFF00FF
# define ORANGE      0xFFA500
# define PURPLE      0x800080
# define PINK        0xFFC0CB
# define BROWN       0x8B4513
# define GRAY        0x808080
# define LIGHT_GRAY  0xD3D3D3
# define DARK_GRAY   0xA9A9A9
# define DEEP_OCEAN  0x00008B  // Bleu foncé (Océan profond)
# define SHALLOW_WATER 0x1E90FF // Bleu clair (Eau peu profonde)
# define SAND        0xF4A460  // Beige/Sable (Plage)
# define GRASSLAND   0x00FF00  // Vert clair (Plaine/Végétation)
# define HILLS       0x008000  // Vert foncé (Collines)
# define MOUNTAIN    0x8B4513  // Marron (Montagnes moyennes)
# define HIGH_MOUNTAIN 0xA9A9A9 // Gris clair (Hautes montagnes)
# define SNOW        0xFFFFFF  // Blanc (Neige sur très haute altitude)
/////////EVENT MLX HOOK//////
# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define EVENT_MOUSE_PRESS 4
# define EVENT_MOUSE_RELEASE 5
# define EVENT_DESTROY 17

# define PI 3.14159265358979323846
# define PI_12 0.261799388
# define PI_24 0.130899694

# define WAIT 0
# define READY 1
# define UP_LEFT 0
# define UP_RIGHT 1
# define DOWN_LEFT 2
# define DOWN_RIGHT 3
#endif
