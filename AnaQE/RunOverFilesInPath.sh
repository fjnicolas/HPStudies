#!/bin/bash

# Base directory containing energy subdirectories (e.g., energy1, energy2, etc.)
#base_dir="/pnfs/sbnd/persistent/users/fnicolas/testg4hp"
#base_dir="/pnfs/sbnd/persistent/users/fnicolas/testg4hp_FTFP"

# base dir is first input argument
base_dir=$1

# program path name is second input argument
program_path=$2

echo "Base directory: $base_dir"
echo "Program path: $program_path"

# Loop over the subdirectories (e.g., energy1, energy2, etc.)
for subdir in "$base_dir"/*; do
    if [ -d "$subdir" ]; then
        
        echo ""
        echo "Running for $(basename "$subdir")"

        # Collect all .root files in the subdirectory
        root_files=$(find "$subdir" -type f -name "*.root")

        if [ ! -z "$root_files" ]; then
            # Create a text file with the list of root files
            file_list_path="file_list_$(basename "$subdir").txt"
           
            # Clear the file if it already exists
            > "$file_list_path"
            
            for root_file in $root_files; do
                # full path to the root file to be written to the file list
                echo "$root_file" >> "$file_list_path"
                
            done
           
            # Output file name
            output_file_name="output_$(basename "$subdir").root"
            echo "Output file name: $output_file_name"
            echo "File list path: $file_list_path"

            # Run the "CreateMCXSec_QE" command
            
            # You can use the command with stdin from file_list_path if necessary
            # Adjust command if "CreateMCXSec_QE" takes arguments from the file list
            cat "$file_list_path"  # Add any other necessary arguments here

            #../../HPStudies/AnaQE/CreateMCXSec_QE "$file_list_path" "$output_file_name"
            "$program_path" "$file_list_path" "$output_file_name"

            # If you want to pipe the file content to the command, use `cat` to pass input
            # cat "$file_list_path" | CreateMCXSec_QE
        else
            echo "No .root files found in $subdir"
        fi
    fi
done
