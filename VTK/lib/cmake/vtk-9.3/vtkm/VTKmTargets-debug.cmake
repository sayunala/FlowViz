#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "vtkm::vtkmdiympi_nompi" for configuration "Debug"
set_property(TARGET vtkm::vtkmdiympi_nompi APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::vtkmdiympi_nompi PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkmdiympi_nompi.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkmdiympi_nompi.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::vtkmdiympi_nompi )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::vtkmdiympi_nompi "${_IMPORT_PREFIX}/lib/vtkmdiympi_nompi.lib" "${_IMPORT_PREFIX}/bin/vtkmdiympi_nompi.dll" )

# Import target "vtkm::cont" for configuration "Debug"
set_property(TARGET vtkm::cont APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::cont PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_cont-9.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_cont-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::cont )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::cont "${_IMPORT_PREFIX}/lib/vtkm_cont-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_cont-9.3.dll" )

# Import target "vtkm::cont_testing" for configuration "Debug"
set_property(TARGET vtkm::cont_testing APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::cont_testing PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_cont_testing-9.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_cont_testing-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::cont_testing )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::cont_testing "${_IMPORT_PREFIX}/lib/vtkm_cont_testing-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_cont_testing-9.3.dll" )

# Import target "vtkm::worklet" for configuration "Debug"
set_property(TARGET vtkm::worklet APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::worklet PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_worklet-9.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_worklet-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::worklet )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::worklet "${_IMPORT_PREFIX}/lib/vtkm_worklet-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_worklet-9.3.dll" )

# Import target "vtkm::filter_core" for configuration "Debug"
set_property(TARGET vtkm::filter_core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_core PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_core-9.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_core-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_core )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_core "${_IMPORT_PREFIX}/lib/vtkm_filter_core-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_core-9.3.dll" )

# Import target "vtkm::filter_clean_grid" for configuration "Debug"
set_property(TARGET vtkm::filter_clean_grid APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_clean_grid PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_clean_grid-9.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkm::worklet"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_clean_grid-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_clean_grid )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_clean_grid "${_IMPORT_PREFIX}/lib/vtkm_filter_clean_grid-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_clean_grid-9.3.dll" )

# Import target "vtkm::filter_connected_components" for configuration "Debug"
set_property(TARGET vtkm::filter_connected_components APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_connected_components PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_connected_components-9.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkm::worklet"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_connected_components-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_connected_components )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_connected_components "${_IMPORT_PREFIX}/lib/vtkm_filter_connected_components-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_connected_components-9.3.dll" )

# Import target "vtkm::filter_vector_analysis" for configuration "Debug"
set_property(TARGET vtkm::filter_vector_analysis APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_vector_analysis PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_vector_analysis-9.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkm::worklet"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_vector_analysis-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_vector_analysis )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_vector_analysis "${_IMPORT_PREFIX}/lib/vtkm_filter_vector_analysis-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_vector_analysis-9.3.dll" )

# Import target "vtkm::filter_mesh_info" for configuration "Debug"
set_property(TARGET vtkm::filter_mesh_info APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_mesh_info PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_mesh_info-9.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkm::worklet"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_mesh_info-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_mesh_info )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_mesh_info "${_IMPORT_PREFIX}/lib/vtkm_filter_mesh_info-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_mesh_info-9.3.dll" )

# Import target "vtkm::filter_contour" for configuration "Debug"
set_property(TARGET vtkm::filter_contour APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_contour PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_contour-9.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkm::worklet"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_contour-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_contour )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_contour "${_IMPORT_PREFIX}/lib/vtkm_filter_contour-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_contour-9.3.dll" )

# Import target "vtkm::filter_density_estimate" for configuration "Debug"
set_property(TARGET vtkm::filter_density_estimate APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_density_estimate PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_density_estimate-9.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkm::worklet"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_density_estimate-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_density_estimate )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_density_estimate "${_IMPORT_PREFIX}/lib/vtkm_filter_density_estimate-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_density_estimate-9.3.dll" )

# Import target "vtkm::filter_entity_extraction" for configuration "Debug"
set_property(TARGET vtkm::filter_entity_extraction APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_entity_extraction PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_entity_extraction-9.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkm::worklet"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_entity_extraction-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_entity_extraction )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_entity_extraction "${_IMPORT_PREFIX}/lib/vtkm_filter_entity_extraction-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_entity_extraction-9.3.dll" )

# Import target "vtkm::filter_field_conversion" for configuration "Debug"
set_property(TARGET vtkm::filter_field_conversion APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_field_conversion PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_field_conversion-9.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkm::worklet"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_field_conversion-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_field_conversion )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_field_conversion "${_IMPORT_PREFIX}/lib/vtkm_filter_field_conversion-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_field_conversion-9.3.dll" )

# Import target "vtkm::filter_field_transform" for configuration "Debug"
set_property(TARGET vtkm::filter_field_transform APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_field_transform PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_field_transform-9.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_field_transform-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_field_transform )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_field_transform "${_IMPORT_PREFIX}/lib/vtkm_filter_field_transform-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_field_transform-9.3.dll" )

# Import target "vtkm::filter_flow" for configuration "Debug"
set_property(TARGET vtkm::filter_flow APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_flow PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_flow-9.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkm::worklet"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_flow-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_flow )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_flow "${_IMPORT_PREFIX}/lib/vtkm_filter_flow-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_flow-9.3.dll" )

# Import target "vtkm::filter_geometry_refinement" for configuration "Debug"
set_property(TARGET vtkm::filter_geometry_refinement APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_geometry_refinement PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_geometry_refinement-9.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_geometry_refinement-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_geometry_refinement )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_geometry_refinement "${_IMPORT_PREFIX}/lib/vtkm_filter_geometry_refinement-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_geometry_refinement-9.3.dll" )

# Import target "vtkm::filter_image_processing" for configuration "Debug"
set_property(TARGET vtkm::filter_image_processing APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_image_processing PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_image_processing-9.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkm::worklet"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_image_processing-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_image_processing )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_image_processing "${_IMPORT_PREFIX}/lib/vtkm_filter_image_processing-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_image_processing-9.3.dll" )

# Import target "vtkm::filter_multi_block" for configuration "Debug"
set_property(TARGET vtkm::filter_multi_block APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_multi_block PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_multi_block-9.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkm::worklet"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_multi_block-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_multi_block )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_multi_block "${_IMPORT_PREFIX}/lib/vtkm_filter_multi_block-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_multi_block-9.3.dll" )

# Import target "vtkm::filter_resampling" for configuration "Debug"
set_property(TARGET vtkm::filter_resampling APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_resampling PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_resampling-9.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkm::worklet"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_resampling-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_resampling )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_resampling "${_IMPORT_PREFIX}/lib/vtkm_filter_resampling-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_resampling-9.3.dll" )

# Import target "vtkm::filter_scalar_topology" for configuration "Debug"
set_property(TARGET vtkm::filter_scalar_topology APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_scalar_topology PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_scalar_topology-9.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_scalar_topology-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_scalar_topology )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_scalar_topology "${_IMPORT_PREFIX}/lib/vtkm_filter_scalar_topology-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_scalar_topology-9.3.dll" )

# Import target "vtkm::filter_zfp" for configuration "Debug"
set_property(TARGET vtkm::filter_zfp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::filter_zfp PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_filter_zfp-9.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkm::worklet"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_filter_zfp-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::filter_zfp )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::filter_zfp "${_IMPORT_PREFIX}/lib/vtkm_filter_zfp-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_filter_zfp-9.3.dll" )

# Import target "vtkm::io" for configuration "Debug"
set_property(TARGET vtkm::io APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::io PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_io-9.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_io-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::io )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::io "${_IMPORT_PREFIX}/lib/vtkm_io-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_io-9.3.dll" )

# Import target "vtkm::source" for configuration "Debug"
set_property(TARGET vtkm::source APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkm::source PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkm_source-9.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkm_source-9.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkm::source )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkm::source "${_IMPORT_PREFIX}/lib/vtkm_source-9.3.lib" "${_IMPORT_PREFIX}/bin/vtkm_source-9.3.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
