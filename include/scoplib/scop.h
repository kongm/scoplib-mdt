
   /*+------- <| --------------------------------------------------------**
    **         A                  Clan/Scop                              **
    **---     /.\   -----------------------------------------------------**
    **   <|  [""M#                  scop.h                               **
    **-   A   | #   -----------------------------------------------------**
    **   /.\ [""M#         First version: 30/04/2008                     **
    **- [""M# | #  U"U#U  -----------------------------------------------**
         | #  | #  \ .:/
         | #  | #___| #
 ******  | "--'     .-"  ******************************************************
 *     |"-"-"-"-"-#-#-##   Clan : the Chunky Loop Analyzer (experimental)     *
 ****  |     # ## ######  *****************************************************
 *      \       .::::'/                                                       *
 *       \      ::::'/     Copyright (C) 2008 Cedric Bastoul                  *
 *     :8a|    # # ##                                                         *
 *     ::88a      ###      This is free software; you can redistribute it     *
 *    ::::888a  8a ##::.   and/or modify it under the terms of the GNU Lesser *
 *  ::::::::888a88a[]:::   General Public License as published by the Free    *
 *::8:::::::::SUNDOGa8a::. Software Foundation, either version 2.1 of the     *
 *::::::::8::::888:Y8888:: License, or (at your option) any later version.    *
 *::::':::88::::888::Y88a::::::::::::...                                      *
 *::'::..    .   .....   ..   ...  .                                          *
 * This software is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY *
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License   *
 * for more details.							      *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public License   *
 * along with software; if not, write to the Free Software Foundation, Inc.,  *
 * 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA                     *
 *                                                                            *
 * Clan, the Chunky Loop Analyzer                                             *
 * Written by Cedric Bastoul, Cedric.Bastoul@inria.fr                         *
 *                                                                            *
 ******************************************************************************/


/*+****************************************************************************
 *  THIS FILE HAS BEEN AUTOMATICALLY GENERATED FROM scop.h.in BY configure    *
 ******************************************************************************/


#ifndef SCOPLIB_SCOP_H
# define SCOPLIB_SCOP_H

# include <unistd.h>

# define SCOPLIB_RELEASE "0.2.3"
# define SCOPLIB_VERSION "64"
# ifndef SCOPLIB_INT_T_IS_LONGLONG
#  define SCOPLIB_INT_T_IS_LONGLONG
# endif

# include <scoplib/macros.h>
# include <scoplib/matrix.h>
# include <scoplib/statement.h>
# include <scoplib/vector.h>


# if defined(__cplusplus)
extern "C"
  {
# endif


/**
 * The scop_t structure stores the useful informations of a static
 * control part of a program to process it within a polyhedral framework.
 */
struct scoplib_scop
{
  scoplib_matrix_p context;     /**< Constraints on the SCoP parameters */
  int nb_parameters;		/**< Number of parameters for the SCoP */
  char ** parameters;           /**< Array of (nb_parameters) parameter names */
  int nb_arrays;                /**< Number of arrays accessed in the SCoP */
  char ** arrays;               /**< Array of (nb_arrays) array names */
  scoplib_statement_p statement;/**< Statement list of the SCoP */
  char* optiontags;	        /**< The content (as a 0 terminated
				   string) of the optional tags. */
  void* usr;		        /**< A user-defined field, not touched
				   by scop. */
};
typedef struct scoplib_scop   scoplib_scop_t;
typedef struct scoplib_scop * scoplib_scop_p;


/*+****************************************************************************
 *                          Structure display function                        *
 ******************************************************************************/
void    scoplib_scop_print_structure(FILE *, scoplib_scop_p, int);
void    scoplib_scop_print(FILE *, scoplib_scop_p);
void    scoplib_scop_print_dot_scop(FILE *, scoplib_scop_p);
void	scoplib_scop_print_dot_scop_options(FILE * file, scoplib_scop_p scop,
					    int options);


/******************************************************************************
 *                               Reading function                             *
 ******************************************************************************/
scoplib_scop_p	scoplib_scop_read(FILE *);
char*		scoplib_scop_tag_content(scoplib_scop_p, char*, char*);
char*		scoplib_scop_tag_content_from_string(char*, char*, char*);


/*+****************************************************************************
 *                    Memory allocation/deallocation function                 *
 ******************************************************************************/
scoplib_scop_p	scoplib_scop_malloc();
void		scoplib_scop_free(scoplib_scop_p);
scoplib_scop_p	scoplib_scop_dup(scoplib_scop_p);
void		scoplib_scop_shallow_free(scoplib_scop_p);
scoplib_scop_p  scoplib_scop_shallow_copy(scoplib_scop_p);


/*+****************************************************************************
 *                            Processing functions                            *
 ******************************************************************************/
void		scoplib_scop_normalize_schedule(scoplib_scop_p);


/*+****************************************************************************
 *                       New Scop manipulation functions                      *
 ******************************************************************************/
/**
 * scoplib_scop_insert_parameters:
 *
 * This function replace all numerical constants in iteration domains
 * by newly introduced parameters.
 *
 * \param scop                 The scop being parameterized (in-place)
 * \param nb_new_parameters    The number of parameters to add
 * \param new_parameter_names  The name of the new parameters.
 * \output scop                The parameterized scop (from a deep copy)
 **
 */
extern
void
scoplib_scop_insert_parameters(scoplib_scop_p scop,
			       const int nb_new_parameters,
			       char** new_parameter_names);
/**
 * scoplib_scop_parameterize_constants_in_domains:
 *
 * This function replace all numerical constants in iteration domains
 * by newly introduced parameters.
 *
 * \param scop             The scop being parameterized
 * \param parameter_slack  The slack for new parameter Ni, e.g.,
 *                         Ni - slack <= scalar value <= Ni + slack
 * \output scop            The parameterized scop (from a deep copy)
 **
 */
extern
scoplib_scop_p
scoplib_scop_parameterize_constants_in_domains(const scoplib_scop_p scop_input,
					       const int parameter_slack);

/**
 * scoplib_scop_insert_negative_params:
 *
 * This function introduce one new parameter mNi for each parameter
 * Ni, such that mNi = -Ni.
 *
 * \param scop             The scop being parameterized
 * \output scop            The parameterized scop (from a deep copy)
 **
 */
extern
scoplib_scop_p
scoplib_scop_insert_negative_params(const scoplib_scop_p scop_input);



# if defined(__cplusplus)
  }
# endif

#endif /* define SCOPLIB_SCOP_H */
