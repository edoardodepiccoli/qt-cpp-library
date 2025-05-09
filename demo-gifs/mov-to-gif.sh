rm -f *.gif

for file in *.mov; do
  ffmpeg -i "$file" -vf "fps=15,scale=800:-1:flags=lanczos" "${file%.mov}.gif"
done