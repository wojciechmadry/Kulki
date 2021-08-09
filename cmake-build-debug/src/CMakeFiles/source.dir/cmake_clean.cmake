file(REMOVE_RECURSE
  "libsource.a"
  "libsource.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/source.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
