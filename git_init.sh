git init
git remote add origin http://github.com/dorbala/latte.git
git remote -v
git pull origin master
git add *
git -c "user.email=dorbala@usc.edu" -c "user.name=dorbala" commit -m "Source files for latte"
git push origin master
