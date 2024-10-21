/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_mathis.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:28:47 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/21 14:32:35 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>

typedef struct {
    double x, y;
} Vector2D;

typedef struct {
    int width, height;
    char **map;
} Map;

typedef struct {
    Vector2D position;
    Vector2D direction;
    double fov;
} Camera;
