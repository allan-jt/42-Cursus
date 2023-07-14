import { Injectable } from '@nestjs/common';
import { Participant, Role } from '@prisma/client';
import { ChatPrismaService } from './prisma.service';

@Injectable()
export class ParticipantService {
  constructor(private chatPrismaService: ChatPrismaService) {}

	async createChannelParticipant(
    user_id: number,
    channel_id: number,
    role: Role,
  ) {
		try{

			const data = {
				channel: {
        connect: { id: channel_id },
      },
      participant: {
        connect: { id: user_id },
      },
      role: role,
      isBanned: false,
      isMuted: false,
      muteFinishAt: null,
    };
    return this.chatPrismaService.participant.create({
			data,
      include: {
				participant: true,
        channel: true,
      },
    });
		}
		catch(err){
			console.log(err);
		}
  }

  async getParticipant(
    userID: number,
    channelID: number,
	){
    const participant =
      await this.chatPrismaService.getParticipantByUserIDAndChannelID(
        parseInt(userID.toString()),
        parseInt(channelID.toString()),
      );
    return participant;
  }

	async getAllParticipantsInChannel(channel_id: number) {
		return await this.chatPrismaService.getAllParticipantsInChannel(channel_id);
	}
}
