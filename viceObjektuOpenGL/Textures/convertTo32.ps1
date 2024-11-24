# Loop from 01 to 13
for ($i = 1; $i -le 13; $i++) {
    # Format the index to always have two digits
    $formattedIndex = $i.ToString("D2")
    
    # Define the input and output file names
    $inputFile = "texture_$formattedIndex.png"
    $outputFile = "texture32_$formattedIndex.png"
    
    # Execute the ImageMagick command
    magick $inputFile PNG32:$outputFile
}
