#!/bin/sh
echo "Enter the commit message:"
read COMMIT_MESSAGE

git add .
git commit -m "$COMMIT_MESSAGE"
git push