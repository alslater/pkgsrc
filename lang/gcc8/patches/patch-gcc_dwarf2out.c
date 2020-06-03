$NetBSD$

--- gcc/dwarf2out.c.orig	2020-05-05 14:45:23.127898129 +0000
+++ gcc/dwarf2out.c
@@ -1458,7 +1458,7 @@ dw_val_equal_p (dw_val_node *a, dw_val_n
       return a->v.val_file == b->v.val_file;
     case dw_val_class_decl_ref:
       return a->v.val_decl_ref == b->v.val_decl_ref;
-    
+
     case dw_val_class_const_double:
       return (a->v.val_double.high == b->v.val_double.high
 	      && a->v.val_double.low == b->v.val_double.low);
@@ -2219,9 +2219,9 @@ output_loc_operands (dw_loc_descr_ref lo
 	unsigned r = val1->v.val_unsigned;
 	if (for_eh_or_skip >= 0)
 	  r = DWARF2_FRAME_REG_OUT (r, for_eh_or_skip);
-	gcc_assert (size_of_uleb128 (r) 
+	gcc_assert (size_of_uleb128 (r)
 		    == size_of_uleb128 (val1->v.val_unsigned));
-	dw2_asm_output_data_uleb128 (r, NULL);	
+	dw2_asm_output_data_uleb128 (r, NULL);
       }
       break;
     case DW_OP_fbreg:
@@ -2232,9 +2232,9 @@ output_loc_operands (dw_loc_descr_ref lo
 	unsigned r = val1->v.val_unsigned;
 	if (for_eh_or_skip >= 0)
 	  r = DWARF2_FRAME_REG_OUT (r, for_eh_or_skip);
-	gcc_assert (size_of_uleb128 (r) 
+	gcc_assert (size_of_uleb128 (r)
 		    == size_of_uleb128 (val1->v.val_unsigned));
-	dw2_asm_output_data_uleb128 (r, NULL);	
+	dw2_asm_output_data_uleb128 (r, NULL);
 	dw2_asm_output_data_sleb128 (val2->v.val_int, NULL);
       }
       break;
@@ -2453,7 +2453,7 @@ output_loc_operands (dw_loc_descr_ref lo
     }
 }
 
-/* Output a sequence of location operations.  
+/* Output a sequence of location operations.
    The for_eh_or_skip parameter controls whether register numbers are
    converted using DWARF2_FRAME_REG_OUT, which is needed in the case that
    hard reg numbers have been processed via DWARF_FRAME_REGNUM (i.e. for unwind
@@ -2467,7 +2467,7 @@ output_loc_sequence (dw_loc_descr_ref lo
     {
       enum dwarf_location_atom opc = loc->dw_loc_opc;
       /* Output the opcode.  */
-      if (for_eh_or_skip >= 0 
+      if (for_eh_or_skip >= 0
           && opc >= DW_OP_breg0 && opc <= DW_OP_breg31)
 	{
 	  unsigned r = (opc - DW_OP_breg0);
@@ -2475,7 +2475,7 @@ output_loc_sequence (dw_loc_descr_ref lo
 	  gcc_assert (r <= 31);
 	  opc = (enum dwarf_location_atom) (DW_OP_breg0 + r);
 	}
-      else if (for_eh_or_skip >= 0 
+      else if (for_eh_or_skip >= 0
 	       && opc >= DW_OP_reg0 && opc <= DW_OP_reg31)
 	{
 	  unsigned r = (opc - DW_OP_reg0);
@@ -2554,13 +2554,13 @@ output_loc_operands_raw (dw_loc_descr_re
     case DW_OP_regx:
       {
 	unsigned r = DWARF2_FRAME_REG_OUT (val1->v.val_unsigned, 1);
-	gcc_assert (size_of_uleb128 (r) 
+	gcc_assert (size_of_uleb128 (r)
 		    == size_of_uleb128 (val1->v.val_unsigned));
 	fputc (',', asm_out_file);
 	dw2_asm_output_data_uleb128_raw (r);
       }
       break;
-      
+
     case DW_OP_constu:
     case DW_OP_plus_uconst:
     case DW_OP_piece:
@@ -2615,7 +2615,7 @@ output_loc_operands_raw (dw_loc_descr_re
     case DW_OP_bregx:
       {
 	unsigned r = DWARF2_FRAME_REG_OUT (val1->v.val_unsigned, 1);
-	gcc_assert (size_of_uleb128 (r) 
+	gcc_assert (size_of_uleb128 (r)
 		    == size_of_uleb128 (val1->v.val_unsigned));
 	fputc (',', asm_out_file);
 	dw2_asm_output_data_uleb128_raw (r);
@@ -3483,7 +3483,7 @@ struct dw_loc_list_hasher : ggc_ptr_hash
 {
 
   typedef const_tree compare_type;
-  
+
   static hashval_t hash (cached_dw_loc_list *);
   static bool equal (cached_dw_loc_list *, const_tree);
 };
@@ -11571,7 +11571,7 @@ output_aranges (void)
 {
   unsigned i;
   unsigned long aranges_length = size_of_aranges ();
-  
+
   if (!XCOFF_DEBUGGING_INFO)
     {
       if (DWARF_INITIAL_LENGTH_SIZE - DWARF_OFFSET_SIZE == 4)
@@ -12583,7 +12583,7 @@ output_one_line_info_table (dw_line_info
 	  dw2_asm_output_data (1, DW_LNS_set_prologue_end,
 			       "set prologue end");
 	  break;
-	  
+
 	case LI_set_epilogue_begin:
 	  dw2_asm_output_data (1, DW_LNS_set_epilogue_begin,
 			       "set epilogue begin");
@@ -17112,7 +17112,7 @@ dw_sra_loc_expr (tree decl, rtx loc)
 	      if (GET_CODE (varloc) == EXPR_LIST)
 		varloc = XEXP (varloc, 0);
 	    }
-	  do 
+	  do
 	    {
 	      if (GET_CODE (varloc) == CONST
 		  || GET_CODE (varloc) == SIGN_EXTEND
@@ -20591,7 +20591,7 @@ compute_frame_pointer_to_fb_displacement
   frame_pointer_fb_offset = -offset;
 
   /* ??? AVR doesn't set up valid eliminations when there is no stack frame
-     in which to eliminate.  This is because it's stack pointer isn't 
+     in which to eliminate.  This is because it's stack pointer isn't
      directly accessible as a register within the ISA.  To work around
      this, assume that while we cannot provide a proper value for
      frame_pointer_fb_offset, we won't need one either.  */
@@ -20626,7 +20626,7 @@ add_name_attribute (dw_die_ref die, cons
    ??? This is a temporary measure until after we're able to generate
    regular DWARF for the complex Ada type system.  */
 
-static void 
+static void
 add_gnat_descriptive_type_attribute (dw_die_ref die, tree type,
 				     dw_die_ref context_die)
 {
@@ -21652,8 +21652,8 @@ add_calling_convention_attribute (dw_die
       /* DWARF 2 doesn't provide a way to identify a program's source-level
 	entry point.  DW_AT_calling_convention attributes are only meant
 	to describe functions' calling conventions.  However, lacking a
-	better way to signal the Fortran main program, we used this for 
-	a long time, following existing custom.  Now, DWARF 4 has 
+	better way to signal the Fortran main program, we used this for
+	a long time, following existing custom.  Now, DWARF 4 has
 	DW_AT_main_subprogram, which we add below, but some tools still
 	rely on the old way, which we thus keep.  */
       value = DW_CC_program;
@@ -23110,9 +23110,9 @@ gen_subprogram_die (tree decl, dw_die_re
 	    {
 	      if (dwarf_version >= 3 || !dwarf_strict)
 		{
-		  /* We should use ranges for non-contiguous code section 
+		  /* We should use ranges for non-contiguous code section
 		     addresses.  Use the actual code range for the initial
-		     section, since the HOT/COLD labels might precede an 
+		     section, since the HOT/COLD labels might precede an
 		     alignment offset.  */
 		  bool range_list_added = false;
 		  add_ranges_by_labels (subr_die, fde->dw_fde_begin,
@@ -23148,7 +23148,7 @@ gen_subprogram_die (tree decl, dw_die_re
 		  if (TREE_PUBLIC (decl))
 		    add_AT_flag (seg_die, DW_AT_external, 1);
 
-		  if (decl_name != NULL 
+		  if (decl_name != NULL
 		      && IDENTIFIER_POINTER (decl_name) != NULL)
 		    {
 		      name = dwarf2_name (decl, 1);
@@ -23162,7 +23162,7 @@ gen_subprogram_die (tree decl, dw_die_re
 		  if (DECL_ARTIFICIAL (decl))
 		    add_AT_flag (seg_die, DW_AT_artificial, 1);
 
-		  name = concat ("__second_sect_of_", name, NULL); 
+		  name = concat ("__second_sect_of_", name, NULL);
 		  add_AT_low_high_pc (seg_die, fde->dw_fde_second_begin,
                                       fde->dw_fde_second_end, false);
 		  add_name_attribute (seg_die, name);
@@ -23327,6 +23327,11 @@ gen_subprogram_die (tree decl, dw_die_re
     /* Add the calling convention attribute if requested.  */
     add_calling_convention_attribute (subr_die, decl);
 
+#ifdef TARGET_SAVE_ARGS
+  if (TARGET_SAVE_ARGS)
+    add_AT_flag (subr_die, DW_AT_SUN_amd64_parmdump, 1);
+#endif
+
   /* Output Dwarf info for all of the stuff within the body of the function
      (if it has one - it may be just a declaration).
 
@@ -25105,7 +25110,7 @@ gen_member_die (tree type, dw_die_ref co
 	{
 	  /* Handle inline static data members, which only have in-class
 	     declarations.  */
-	  dw_die_ref ref = NULL; 
+	  dw_die_ref ref = NULL;
 	  if (child->die_tag == DW_TAG_variable
 	      && child->die_parent == comp_unit_die ())
 	    {
@@ -27145,7 +27150,7 @@ gen_scheduled_generic_parms_dies (void)
 
   if (!generic_type_instances)
     return;
-  
+
   FOR_EACH_VEC_ELT (*generic_type_instances, i, t)
     if (COMPLETE_TYPE_P (t))
       gen_generic_params_dies (t);
@@ -27909,7 +27914,7 @@ dwarf2out_source_line (unsigned int line
      that second line number entry.  */
   /* Recall that this end-of-prologue indication is *not* the same thing
      as the end_prologue debug hook.  The NOTE_INSN_PROLOGUE_END note,
-     to which the hook corresponds, follows the last insn that was 
+     to which the hook corresponds, follows the last insn that was
      emitted by gen_prologue.  What we need is to precede the first insn
      that had been emitted after NOTE_INSN_FUNCTION_BEG, i.e. the first
      insn that corresponds to something the user wrote.  These may be
@@ -28171,7 +28176,7 @@ output_macinfo_op (macinfo_entry *ref)
       file_num = maybe_emit_file (fd);
       dw2_asm_output_data (1, DW_MACINFO_start_file, "Start new file");
       dw2_asm_output_data_uleb128 (ref->lineno,
-				   "Included from line number %lu", 
+				   "Included from line number %lu",
 				   (unsigned long) ref->lineno);
       dw2_asm_output_data_uleb128 (file_num, "file %s", ref->info);
       break;
@@ -28194,7 +28199,7 @@ output_macinfo_op (macinfo_entry *ref)
       dw2_asm_output_data (1, ref->code,
 			   ref->code == DW_MACINFO_define
 			   ? "Define macro" : "Undefine macro");
-      dw2_asm_output_data_uleb128 (ref->lineno, "At line number %lu", 
+      dw2_asm_output_data_uleb128 (ref->lineno, "At line number %lu",
 				   (unsigned long) ref->lineno);
       dw2_asm_output_nstring (ref->info, -1, "The macro");
       break;
@@ -30598,7 +30603,7 @@ hash_loc_operands (dw_loc_descr_ref loc,
 		      get_full_len (*val2->v.val_wide)
 		      * HOST_BITS_PER_WIDE_INT / HOST_BITS_PER_CHAR);
 	  break;
-	case dw_val_class_addr:	
+	case dw_val_class_addr:
 	  inchash::add_rtx (val2->v.val_addr, hstate);
 	  break;
 	default:
@@ -31280,7 +31285,7 @@ dwarf2out_finish (const char *)
 
   /* We can only use the low/high_pc attributes if all of the code was
      in .text.  */
-  if (!have_multiple_function_sections 
+  if (!have_multiple_function_sections
       || (dwarf_version < 3 && dwarf_strict))
     {
       /* Don't add if the CU has no associated code.  */
