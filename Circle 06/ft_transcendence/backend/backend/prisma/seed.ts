const { PrismaClient } = require('@prisma/client');
import { users } from './seeding/User';
import { friends } from './seeding/Friend';
import { games } from './seeding/Game';
import { channels } from './seeding/channel';

const prisma = new PrismaClient();

async function main() {
  for (let user of users) {
    await prisma.user.create({
      data: user,
    });
  }
  for (let channel of channels) {
    	await prisma.channel.create({
    		data: channel,
    	});
    }
  // for (let game of games) {
  //   await prisma.game.create({
  //     data: game,
  //   });
  // }
  // for (let friend of friends) {
  // 	await prisma.friend.create({
  // 		data: friend,
  // 	});
  // }
}

main()
  .catch((e) => {
    console.error(e);
    process.exit(1);
  })
  .finally(async () => {
    await prisma.$disconnect();
  });
