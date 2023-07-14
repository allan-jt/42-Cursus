import { HttpException, Injectable, UnauthorizedException } from '@nestjs/common';
import { UserPrismaService } from 'src/prisma/user.prisma';
import { FriendPrismaService } from 'src/prisma/friend.prisma';
import { GamePrismaService } from 'src/prisma/game.prisma';
import { Game, User } from '@prisma/client';

export interface UserWithGames extends User {
  gamesPlayer1: Game[];
  gamesPlayer2: Game[];
  gamesWon: Game[];
}

export interface Player extends User {
  id: number;
  username: string;
  image: string;
}


@Injectable()
export class UsersService {
  constructor(
    public userPrisma: UserPrismaService,
    private friendPrisma: FriendPrismaService,
  ) {}

  /*	Getters___________________________________________________________________*/
  async getData(id: number, attributes: string) {
    const user = await this.userPrisma.getUser({ id: id });
    if (user == undefined || user == null) return undefined;

    const listOfAtributes = attributes.split(' ');
    const filteredAtributes = Object.entries(user).filter(([key, value]) =>
      listOfAtributes.includes(key),
    );

    return Object.fromEntries(filteredAtributes);
  }

  // async getAchievements(id: number) {
  //   const user = await this.userPrisma.getUser({ id: id });
  //   if (!user) return {};
    
  //   return user.achievements;
  // }

  async MatchesHistory (id: number) {
    const userGame = (await this.userPrisma.getUser(
      { id: id },
      {
        gamesPlayer1: { },
        gamesPlayer2: { },
      },
    )) as UserWithGames;

    if (userGame == undefined || userGame == null) {
      return [];
    }

    const games1: Game[] = userGame.gamesPlayer1 || [];
    const games2: Game[] = userGame.gamesPlayer2 || [];
    const games = games1.concat(games2);
    
    const matchesHistory = games.map(game => {
      const date = game.startAt.toLocaleDateString('en-US', { day: '2-digit', month: '2-digit', year: 'numeric' });
      const durationMinutes = Math.floor((game.finishAt.getTime() - game.startAt.getTime()) / 60000);
      const durationSeconds = Math.floor((game.finishAt.getTime() - game.startAt.getTime()) % 60000) / 1000;

      let durationMin = "";
      if (durationMinutes) {
        durationMin = durationMinutes == 1 ? `${durationMinutes} minute` : `${durationMinutes} minutes`;
      }
      const durationSec = durationSeconds == 1 ? `${Math.floor(durationSeconds)} second` : `${Math.floor(durationSeconds)} seconds`;
      const duration = durationMinutes ? 
      `${durationMin} and ${durationSec}` : 
      `${durationSec}`;

      const score = `${game.score1} : ${game.score2}`;
      return {
        player1_id: game.player1_id,
        player1_name: '',
        player1_image: '',
        player2_id: game.player2_id,
        player2_name: '',
        player2_image: '',
        date,
        duration: `${duration}`,
        score,
        opponentName: '',
        opponentImage: '',
      };
    });

    for (let i = 0; i < matchesHistory.length; i++) {
      const user1_id = matchesHistory[i].player1_id;
      const user2_id = matchesHistory[i].player2_id;
      if (user1_id) {
        const user1 = await this.userPrisma.getUser({ id: user1_id });
        if (user1) {
          matchesHistory[i].player1_name = user1.username;
          matchesHistory[i].player1_image = user1.image;
        }
      }
      if (user2_id) {
        const user2 = await this.userPrisma.getUser({ id: user2_id });
        if (user2) {
          matchesHistory[i].player2_name = user2.username;
          matchesHistory[i].player2_image = user2.image;
        }
      }
    }

    return matchesHistory;
  }

  async getAllUsers(id: number) {
    const friendIds = await this.friendPrisma
      .getFriends({
        where: { OR: [{ friend1_id: id }, { friend2_id: id }] },
      })
      .then((friends) =>
        friends.map((friend) =>
          friend.friend1_id == id ? friend.friend2_id : friend.friend1_id,
        ),
      );

    const users = await this.userPrisma.getUsers({
      where: { id: { not: id, notIn: friendIds } },
    });

    return users;
  }

  async getListAllUsers (attributes: string) {
    const listOfAttributes = attributes.split(' ');
    const users = await this.userPrisma.getUsers({});
    if (!users) return {};
    // Use prisma --> ALLAN
    const usersList = users.map((user) => {
      const filteredAttributes = Object.entries(user).filter(([key]) =>
        listOfAttributes.includes(key),
      );
      return Object.fromEntries(filteredAttributes);
    });

    return usersList;
  }


  /*	Setters___________________________________________________________________*/
  async addUser(profile: any): Promise<User> {
    const user = await this.userPrisma.getUser({ id: profile.id });
    if (user !== undefined && user !== null) return user;

    try {
      return await this.userPrisma.createUser({
        id: profile.id,
        intraLogin: profile.login,
      }); 
    } catch (error) {
      console.log("Error here");
      throw new HttpException(error.message, 500, { cause: error });
    }
  }

  async setData(id: number, attributes: { [key: string]: string | any }): Promise<User> {
    const user = await this.userPrisma.getUser({ id: id });
    if (user == undefined || user == null) return undefined;

    try {
      this.ensureCorrectFormat(attributes);
      return await this.userPrisma.updateUser({ id: id }, attributes);
    } catch (error) {
      throw new HttpException(error.message, 500, { cause: error });
    }
  }

  async setUsername(id: number, username: string): Promise<boolean> {
    const user = await this.userPrisma.getUser({ id: id });
    if (!user) return false;

    username = username.trim();
    const validUsernameRegex = /^(?=.*[a-zA-Z])[a-zA-Z0-9_]+$/;
    if (
      username.length == 0 ||
      username.length > 15 ||
      validUsernameRegex.test(username) == false
    ) {
      return false;
    }
    
    try {
      await this.userPrisma.updateUser({ id: id }, { username: username });
      return true;
    } catch (error) {
      return false;
    }
  }

  // async setAvatar(id: number, avatar: string) {
  //   const user = await this.userPrisma.getUser({ id: id });
  //   if (!user) return new Error(`No user by id ${id} exists`);

  //   await this.userPrisma.updateUser({ id: id }, { image: avatar });
  // }
  
  ensureCorrectFormat(attributes: { [key: string]: string | any }) {
    for (const [key, value] of Object.entries(attributes)) {
      if (key === 'enable2FA') {
        attributes[key] = Boolean(value);
        continue;
      } else if (key === 'loggedin') {
        continue;
      }

      const val = Number(value);
      if (!isNaN(val) && isFinite(val) == true) {
        attributes[key] = val;
      }
    }
  }

  /*	Updates___________________________________________________________________*/
  async updateGameInfo(user_id: number) {
    const user = (await this.userPrisma.getUser(
      { id: user_id },
      {
        gamesPlayer1: { },
        gamesPlayer2: { },
        gamesWon: { },
      },
    )) as UserWithGames;
    if (user == undefined || user == null) return;
    
    const wins = user.gamesWon ? user.gamesWon.length : 0;
    const player1Games = user.gamesPlayer1 ? user.gamesPlayer1.length : 0;
    const player2Games = user.gamesPlayer2 ? user.gamesPlayer2.length : 0;
    const loses = player1Games + player2Games - wins;
    
    try {
      await this.userPrisma.updateUser(
        { id: user_id },
        { wins, loses }
      );
    } catch (error) {
      throw new HttpException(error.message, 500, { cause: error });
    }
    
  }

  /*	Block___________________________________________________________________*/
  async blockUser(user_id: number, blocked_id: number) {
    const user = await this.userPrisma.getUser({ id: user_id });
    if (!user) return new Error(`No user by id ${user_id} exists`);

    const blocked = await this.userPrisma.getUser({ id: blocked_id });
    if (!blocked) return new Error(`No user by id ${blocked_id} exists`);

		const data = {
			blockedUser: { connect: { id: blocked_id } },
			blockedByUser: { connect: { id: user_id } },
		};

    return await this.userPrisma.addBlockedUser(data);
  }

	async unblockUser(user_id: number, blocked_id: number) {
		const user = await this.userPrisma.getUser({ id: user_id });
    if (!user) return new Error(`No user by id ${user_id} exists`);

    const blocked = await this.userPrisma.getUser({ id: blocked_id });
    if (!blocked) return new Error(`No user by id ${blocked_id} exists`);

		const blockedUser = await this.userPrisma.getBlockedUser(blocked_id, user_id);
		if (!blockedUser) return new Error(`No blocked user by id ${blocked_id} exists`);
		
		return await this.userPrisma.deleteBlockedUser({ id: blockedUser.id });
	}

	async getBlockedUsers(user_id: number) {
		const user = await this.userPrisma.getUser({ id: user_id });
    if (!user) return new Error(`No user by id ${user_id} exists`);

		return await this.userPrisma.getBlockedUsers(user_id);
	}

	async amIBlockedByUser(user_id: number, blocked_id: number) {
		const user = await this.userPrisma.getUser({ id: user_id });
		if (!user) return new Error(`No user by id ${user_id} exists`);

		const blocked = await this.userPrisma.getUser({ id: blocked_id });
		if (!blocked) return new Error(`No user by id ${blocked_id} exists`);

		const blockedUser = await this.userPrisma.getBlockedUser(blocked_id, user_id);
		if (!blockedUser) return false;
		return true;
	}
}
