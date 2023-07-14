import { Injectable, OnModuleInit } from '@nestjs/common';
import {
  PrismaClient,
  Channel,
  Message,
  Prisma,
  Participant,
  User,
} from '@prisma/client';

@Injectable()
export class ChatPrismaService extends PrismaClient implements OnModuleInit {
  constructor() {
    super({
      datasources: {
        db: {
          url: process.env.DATABASE_URL,
        },
      },
    });
  }

  async onModuleInit() {
    await this.$connect();
  }

  /*	Create Participant */
  async createParticipant(
    data: Prisma.ParticipantCreateInput,
  ): Promise<Participant> {
    return this.participant.create({ data });
  }

  /*	Update Participant */
  async updateParticipant(
    where: Prisma.ParticipantWhereUniqueInput,
    data: Prisma.ParticipantUpdateInput,
  ): Promise<Participant> {
    return this.participant.update({ data, where });
  }

  /*	Get Participant */
  async getParticipant(
    where: Prisma.ParticipantWhereUniqueInput,
  ): Promise<Participant> {
    return this.participant.findUnique({ where });
  }

  async getParticipantByUserIDAndChannelID(userID: number, channelID: number) {
    const participant = await this.participant.findFirst({
      where: {
        channel_id: channelID,
        user_id: userID,
      },
      select: {
        id: true,
        role: true,
        isBanned: true,
        isMuted: true,
        channel_id: true,
        muteFinishAt: true,
        participant: {
          select: {
            id: true,
            username: true,
          },
        },
      },
    });
    return participant;
  }

  //function to get all participants in a channel including the user name
  async getAllParticipantsInChannel(channelID: number) {
    const participants = await this.participant.findMany({
      where: {
        channel_id: channelID,
        role: {
          not: 'INVITED',
        },
      },
      select: {
        role: true,
        isBanned: true,
        isMuted: true,
        muteFinishAt: true,
        participant: {
          select: {
            id: true,
            username: true,
            available: true,
            gameStatus: true,
          },
        },
      },
    });
    return participants;
  }

  async getAvailableUsersNotInChannel(channelID: number) {
    const users = await this.user.findMany({
      where: {
        NOT: {
          participant: {
            some: {
              channel_id: channelID,
            },
          },
        },
      },
      select: {
        id: true,
        username: true,
      },
    });
    return users;
  }

  async getAllChannelsUserIsInvitedTo(userID: number) {
    const channels = await this.participant.findMany({
      where: {
        user_id: userID,
        role: 'INVITED',
      },
      select: {
        channel: {
          select: {
            id: true,
            name: true,
            isDirect: true,
            isPublic: true,
            createdAt: true,
          },
        },
      },
    });
    return channels;
  }

	async getDirectChannelBetweenUsers(user1ID: number, user2ID: number) {
		const channel = await this.channel.findFirst({
			where: {
				AND: [
				{isDirect: true},
				{participants: { some: { user_id: user1ID } }},
				{participants: { some: { user_id: user2ID } }},
				],
		},
		});
		return channel;
	}
	

  /*	Delete Participant */
  async deleteParticipant(
    where: Prisma.ParticipantWhereUniqueInput,
  ): Promise<Participant> {
    return this.participant.delete({ where });
  }

  // async deleteAllParticipantsInChannel(): Promise<Participant[]> {
  // }

  /*	Get Channel */
  async getChannel(where: Prisma.ChannelWhereUniqueInput) {
    return this.channel.findUnique({ where });
  }

  /*	Get Public Channels */
  async getAllPublicChannels() {
    return this.channel.findMany({
      where: {
        isPublic: true,
        isDirect: false,
      },
      select: {
        id: true,
        name: true,
        isDirect: true,
        isPublic: true,
        createdAt: true,
      },
    });
  }

  async getAllPublicChannelsNotJoined(userID: number) {
    const channels = await this.channel.findMany({
      where: {
        isPublic: true,
        isDirect: false,
        participants: {
          none: {
            user_id: userID,
          },
        },
      },
      select: {
        id: true,
        name: true,
        isDirect: true,
        isPublic: true,
        createdAt: true,
				password: true,
      },
    });

		const modifiedChannels = channels.map(channel => ({
			...channel,
			password: channel.password ? 'passwordExists' : '',
		}));

    return modifiedChannels;
  }

  /*	Get Joined Channels */
  async getAllJoinedChannels(userID: number) {
    const channels = await this.channel.findMany({
      where: {
        participants: {
          some: {
            user_id: userID,
            role: {
              not: 'INVITED',
            },
						isBanned: false,
          },
        },
      },
      select: {
        id: true,
        name: true,
        isDirect: true,
        isPublic: true,
        createdAt: true,
      },
    });
    return channels;
  }

  /*	Create Channel	*/
  async createChannel(data: Prisma.ChannelCreateInput): Promise<Channel> {
    return this.channel.create({ data });
  }

  /*	Change the Channel Name */
  async updateChannel(
    where: Prisma.ChannelWhereUniqueInput,
    data: Prisma.ChannelUpdateInput,
  ): Promise<Channel> {
    return this.channel.update({ data, where });
  }

  /*	Delete a Channel */
  async deleteChannel(where: Prisma.ChannelWhereUniqueInput): Promise<Channel> {
    return this.channel.delete({ where });
  }

  async deleteParticipantsInChannel(channelID: number): Promise<any> {
    return this.participant.deleteMany({
      where: {
        channel_id: channelID,
      },
    });
  }

  /*	Message	*/
  async createMessage(data: Prisma.MessageCreateInput): Promise<Message> {
    return this.message.create({ data });
  }

  async getMessage(where: Prisma.MessageWhereUniqueInput): Promise<Message> {
    return this.message.findUnique({ where });
  }

  async getAllMessagesInChannel(channelID: number): Promise<any[]> {
    return this.message.findMany({
      where: {
        channel_id: channelID,
      },
      select: {
        id: true,
        sender_id: true,
        channel_id: true,
        messageBody: true,
        createdAt: true,
        sender: {
          select: {
            id: true,
            username: true,
          },
        },
      },
    });
  }

  async getTopMessagesInChannel(channelID: number): Promise<Message[]> {
    return this.message.findMany({
      where: {
        channel_id: channelID,
      },
      take: 50,
      orderBy: {
        createdAt: 'desc',
      },
    });
  }

	async deleteMessagesInChannel(channelID: number): Promise<any> {
		return this.message.deleteMany({
			where: {
				channel_id: channelID,
			},
		});
	}
}
