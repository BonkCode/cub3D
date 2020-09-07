/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_events.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 17:03:29 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/01 17:03:53 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef X11_EVENTS_H
# define X11_EVENTS_H
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define BUTTON_PRESS 4
# define BUTTON_RELEASE 5
# define MOTION_NOTIFY 6
# define ENTER_NOTIFY 7
# define LEAVE_NOTIFY 8
# define FOCUS_IN 9
# define FOCUS_OUT 10
# define DESTROY_NOTIFY 17
# define NO_EVENT_MASK 0L
# define KEY_PRESS_MASK 1L<<0
# define KEY_RELEASE_MASK 1L<<1
# define BUTTON_PRESS_MASK 1L<<2
# define BUTTON_RELEASE_MASK 1L<<3
# define ENTER_WINDOW_MASK 1L<<4
# define LEAVE_WINDOW_MASK 1L<<5
# define POINTER_MOTION_MASK 1L<<6
# define POINTER_MOTION_HINT_MASK 1L<<7
# define STRUCTURE_NOTIFY_MASK 1L<<17
#endif
