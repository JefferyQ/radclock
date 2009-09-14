/*
 * Copyright (C) 2006-2009 Julien Ridoux <julien@synclab.org>
 *
 * This file is part of the radclock program.
 * 
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _STAMPINPUT_INT_H
#define _STAMPINPUT_INT_H

#define INPUT_OPS(x) x->def

/**
 * Private stamp source definiton
 * All fields compulsary
 */
struct stampsource_def
{
	/** 
	 * Initialise the source
	 */
	int (*init)(struct radclock *handle, struct stampsource *source);
	/**
	 * Get the next stamp, return 0 on sucess
	 */
	int (*get_next_stamp)(struct radclock *handle, struct stampsource *source, struct bidir_stamp *stamp);

	/**
	 * Break blocking loop getting packets
	 */
	void (*source_breakloop)(struct radclock *handle, struct stampsource *source);
	
	/**
	 * Clean up
	 */
	void (*destroy)(struct radclock *handle, struct stampsource *source);
	/**
	 * Update source BPF filter
	 */
	int (*update_filter)(struct radclock *handle, struct stampsource *source);
	/**
	 * Update source RAW file dump out 
	 */
	int (*update_dumpout)(struct radclock *handle, struct stampsource *source);
};

struct stampsource
{
	/**
	 * Sources may use this pointer to store any data
	 */
	void *priv_data;
	/**
	 * The current definition.
	 * Sources shouldn't need to touch this
	 */
	struct stampsource_def *def;

	struct timeref_stats ntp_stats;
};

#endif
