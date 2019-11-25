/**
 * 
 *     libhelper
 *     Copyright (C) 2019, @h3adsh0tzz
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
*/

#include "macho.h"


mach_symtab_command_t *mach_symtab_command_create ()
{
    mach_symtab_command_t *symt = malloc(sizeof(mach_symtab_command_t));
    memset (symt, '\0', sizeof(mach_symtab_command_t));
    return symt;
}

mach_symtab_command_t *mach_symtab_command_load (file_t *file, off_t offset)
{
    mach_symtab_command_t *symt = mach_symtab_command_create ();
    symt = (mach_symtab_command_t *) file_load_bytes (file, sizeof(mach_symtab_command_t), offset);

    if (!symt) {
        g_print ("[*] Error: Problem loading Mach Symbol Table at offset: 0x%llx\n", offset);
        return NULL;
    }

    return symt;
}


//////////////////////////////////////////////////////////////////////////
//                        Mach-O String Table                           //
//////////////////////////////////////////////////////////////////////////

GSList *mach_load_string_table (file_t *file, mach_symtab_command_t *symbol_table)
{
    size_t s = symbol_table->strsize;
    off_t off = symbol_table->stroff;

    char *tmp = file_load_bytes (file, s, off);
    GSList *ret = NULL;
    GString *curr = g_string_new ("");

    for (int i = 0; i < s; i++) {
        if (tmp[i] != 0x0) {
            curr = g_string_append_c (curr, tmp[i]);
        } else {
            if (curr->len > 0 && curr->str) ret = g_slist_append (ret, curr->str);
            curr = g_string_new ("");
        }
    }

    for (int i = 0; i < g_slist_length (ret); i++) {
        char *t = (char *) g_slist_nth_data (ret, i);
        g_print ("table[%d]: %s\n", i, t);
    }

    return ret;
}

char *mach_load_string_from_table (macho_t *macho, int pos)
{
    size_t s = g_slist_length (macho->strings);
    if (!s || pos > s) {
        g_print ("[*] Error: String table is empty\n");
        return "[empty]";
    }
    return g_slist_nth_data (macho->strings, pos);
}


//////////////////////////////////////////////////////////////////////////
//                        Mach-O String Table                           //
//////////////////////////////////////////////////////////////////////////

GSList *mach_load_symbol_table_info (file_t *file, mach_symtab_command_t *symbol_table)
{
    size_t s = symbol_table->nsyms;
    off_t off = symbol_table->symoff;

    // test
    GSList *strtest = mach_load_string_table (file, symbol_table);

    for (int i = 0; i < s; i++) {
        nlist *tmp = (nlist *) file_load_bytes (file, 16, off);

        g_print ("sym name: %d\n", tmp->n_strx);
        g_print ("sym type: %d\n", tmp->n_type);
        g_print ("sym section: %d\n\r", tmp->n_sect);
        //g_print ("sym desc: %d\n", tmp->n_desc);
        //g_print ("sym val: %lu\n", tmp->n_value);

        off += sizeof(nlist);
    }

    return NULL;
}