/***************************************************************/
/**                                                           **/
/**   Luca Tornato Serafini                         9345064   **/
/**   Lucas Moreira Santos                          9345064   **/
/**   Exercício-Programa 01                                   **/
/**   Professor:  Fernando Mário de Oliveira Filho            **/
/**   MAC0122 - Princípios de Desenvolvimento de Algoritmos   **/
/**                                                           **/
/***************************************************************/

/*
  graphics.h

  A simple graphics library.
*/

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

// Types of sampling.
#define GRID_SAMPLE   0   // Sample on uniform grid.
#define RANDOM_SAMPLE 1   // Sample on random points.

// Error codes for save_pgm.
#define EMPTY_IMAGE_ERROR 1  // Image is empty.
#define MEMORY_ERROR      2  // Memory allocation error during saving.

// Graphics object.
typedef struct drawing_struct *Drawing;

/*
  Creates an empty drawing and returns it.
*/
Drawing create_drawing();

/*
  Destroys a drawing, freeing all memory occupied by it.
*/
void destroy_drawing(Drawing D);

/*
  Adds a line segment to a drawing.

  ARGUMENTS:

  - D -- the drawing to which the segment will be added.

  - x1, y1, x2, y2 -- endpoints of the line segment: (x1, y1) and 
    (x2, y2).

  - thickness -- line thickness.

  Returns nonzero on success, zero if it fails to add the line segment.
*/
int add_line_segment(Drawing D, double x1, double y1, double x2, double y2,
                     double thickness);

/*
  Adds a circle to the the drawing.

  ARGUMENTS:

  - D -- the drawing to which the circle will be added.

  - x, y -- center of the circle.

  - r -- radius.

  - thickness -- line thickness.

  - filled -- nonzero if the circle is filled; zero otherwise.

  Returns nonzero on success, zero if it fails to add the circle.
*/
int add_circle(Drawing D, double x, double y, double r,
               double thickness, int filled);

/*
  Saves drawing as a PGM file.

  ARGUMENTS:

  - D -- the drawing.

  - pix_per_unit -- number of pixels to be used per unit.

  - sample_type -- type of sampling technique. GRID_SAMPLE means that
    a uniform grid of size sample_size x sample_size is sampled inside
    a pixel. RANDOM_SAMPLE means that sample_size random points are
    sampled inside each pixel.

  - sample_size -- determines size of sample; see sample_type above.

  - outfile -- output stream.

  Returns zero if the image was saved successfuly, or an error code
  (see top of this file) otherwise.
*/
int save_pgm(Drawing D, int pix_per_unit, int sample_type, int sample_size,
             FILE *outfile);

#endif