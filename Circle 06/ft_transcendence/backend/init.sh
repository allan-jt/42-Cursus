cd /app/backend

npm install 

cd prisma 
echo "y" | npx prisma migrate dev init-$(date +%s) --preview-feature
npx prisma generate
# npx prisma db seed #

cd ..
npx prisma studio | npm run start:dev 
# npx prisma migrate dev --name "init"
# npx prisma db seed
# npx prisma studio
# npx prisma studio | npm run start:dev | npx prisma db seed
# npm run start:dev