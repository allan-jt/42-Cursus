import { Injectable } from '@nestjs/common';
import { FriendPrismaService } from 'src/prisma/friend.prisma';
import { UserPrismaService } from 'src/prisma/user.prisma';
import { UsersService } from 'src/users/users.service';

@Injectable()
export class FriendsService {
  constructor(
    private friendPrisma: FriendPrismaService,
    private userPrisma: UserPrismaService,
    private userService: UsersService,
  ) {}

  /*	Getters___________________________________________________________________*/

  async getFriendsIds(id: number) {
    const friends = await this.friendPrisma.getFriends({
      where: {
        OR: [{ friend1_id: id }, { friend2_id: id }],
        NOT: { id: id },
      },
    });

    const friendIds = friends.flatMap((friend) => {
      if (friend.friend1_id === id) {
        return friend.friend2_id;
      } else if (friend.friend2_id === id) {
        return friend.friend1_id;
      }
      return [];
    });

    const uniqueFriendIds = [...new Set(friendIds)];
    return uniqueFriendIds;
  }

  async checkFriendship(userId1: number, userId2: number): Promise<boolean> {
    const friendship = await this.friendPrisma.getFriends({
      where: {
        OR: [
          { friend1_id: userId1, friend2_id: userId2 },
          { friend1_id: userId2, friend2_id: userId1 },
        ],
      },
    });
    return !!friendship[0];
  }

  async getAllFriends(id: number) {
    const user = await this.userPrisma.getUser({ id: id });
    if (!user) return {};

    const uniqueFriendIds = await this.getFriendsIds(id);
    const friendsDetails = await this.userPrisma.getUsers({
      where: {
        id: {
          in: uniqueFriendIds,
        },
      },
    });

    const friendsList = friendsDetails.map((friend) => {
      return {
        id: friend.id,
        username: friend.username,
        image: friend.image,
        rating: friend.rating,
        available: friend.available,
        gameStatus: friend.gameStatus,
        friendship: true,
      };
    });

    return friendsList;
  }

  async getOnlineFriends(id: number) {
    const user = await this.userPrisma.getUser({ id: id });
    if (!user) return {};

    const uniqueFriendIds = await this.getFriendsIds(id);
    const onlineFriends = [];
    for (const friendId of uniqueFriendIds) {
      const friend = await this.userPrisma.getUser({ id: friendId });
      if (friend && friend.available === 'ONLINE') {
        onlineFriends.push({
          id: friend.id,
          username: friend.username,
          image: friend.image,
          rating: friend.rating,
          available: friend.available,
          gameStatus: friend.gameStatus,
          friendship: true,
        });
      }
    }

    return onlineFriends;
  }

  /*	Setters___________________________________________________________________*/
  async addFriend(userId1: number, username2: string) {
    const user1 = await this.userPrisma.getUser({ id: userId1 });
    const user2 = await this.userPrisma.getUser({ username: username2 });
    const userId2 = user2.id;

    if (
      (await this.userService.amIBlockedByUser(user2.id, user1.id)) ||
      (await this.userService.amIBlockedByUser(user1.id, user2.id))
    ) {
      throw new Error('You are blocked by this user / you blocked this user');
    }

    if (user1.id === user2.id) {
      throw new Error('You can not be your own friend');
    }

    if (!user1 || !user2) {
      throw new Error('One or both users do not exist');
    }

    const existingFriend = await this.checkFriendship(userId1, userId2);
    if (existingFriend) {
      throw new Error('Friendship already exists');
    }

    const newFriendship = await this.friendPrisma.createFriend({
      friend1: { connect: { id: userId1 } },
      friend2: { connect: { id: userId2 } },
    });

    return newFriendship;
  }

  async deleteFriend(userId1: number, userId2: number) {
    const friendship = await this.friendPrisma.getFriends({
      where: {
        OR: [
          { friend1_id: userId1, friend2_id: userId2 },
          { friend1_id: userId2, friend2_id: userId1 },
        ],
      },
    });

    if (friendship[0]) {
      await this.friendPrisma.deleteFriend({ id: friendship[0].id });
      return 'Friendship deleted successfully';
    } else {
      throw new Error('Friendship not found');
    }
  }
}
