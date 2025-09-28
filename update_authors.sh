#!/bin/bash
cd src/

# Update all files with "Taden Marston & Mark Van Horn" to "Gary Sibanda"
for file in *.cpp *.h; do
    if grep -q "Taden Marston & Mark Van Horn" "$file"; then
        sed -i '' 's/Taden Marston & Mark Van Horn/Gary Sibanda/g' "$file"
        echo "Updated $file"
    fi
done

# Update test files that have placeholder author
for file in test*.cpp test*.h; do
    if grep -q "<your name here>" "$file"; then
        sed -i '' 's/<your name here>/Gary Sibanda/g' "$file"
        echo "Updated $file"
    fi
done

echo "Author updates complete!"
