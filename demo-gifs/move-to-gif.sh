# Convert all .mov files to .gif (requires ffmpeg)
# I love ffmpeg
for file in *.mov; do
  ffmpeg -i "$file" -vf "fps=10,scale=320:-1:flags=lanczos" "${file%.mov}.gif"
done
