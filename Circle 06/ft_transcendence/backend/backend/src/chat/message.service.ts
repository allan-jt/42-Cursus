import { Injectable } from '@nestjs/common';
import { ChatPrismaService } from './prisma.service';
import { Message } from '@prisma/client';

@Injectable()
export class MessageService {
  constructor(private chatPrismaService: ChatPrismaService) {}

  /* Messages */
  async createMessage(
    sender_id: number,
    channel_id: number,
    messageBody: string,
  ): Promise<Message> {
    // const participant =
    //   await this.chatPrismaService.getParticipantByUserIDAndChannelID(
    //     sender_id,
    //     channel_id,
    //   );

    const data = {
      sender: { connect: { id: sender_id } },
      channel: { connect: { id: channel_id } },
      messageBody: messageBody,
      createdAt: new Date(),
    };
    try {
			return await this.chatPrismaService.createMessage(data);
		}
		catch(err){
			console.log(err);
		}
  }

  async getMessageByID(id: number): Promise<Message> {
    return await this.chatPrismaService.getMessage({ id: id });
  }

  async getAllMessagesInChannel(channel_id: number) {
    return await this.chatPrismaService.getAllMessagesInChannel(channel_id);
  }

	async getTopMessagesInChannel(channel_id: number) {
		return await this.chatPrismaService.getTopMessagesInChannel(channel_id);
	}	
}