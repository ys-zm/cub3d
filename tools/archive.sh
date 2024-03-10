NAME=$1
TAG=archive/$NAME

echo archiving branch $NAME to tag $TAG
echo Checking out branch $NAME
git checkout $NAME
echo Created $TAG
git tag $TAG $NAME
echo Checking out branch main
git checkout main
echo Deleting $NAME
git branch -d $NAME

echo Pushing tag $TAG to remote
git push origin $TAG
echo Deleting $NAME on remote
git push -d origin $NAME

