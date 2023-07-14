import { Injectable } from '@nestjs/common';
import { PrismaService } from './prisma.service';
import { Friend, Prisma, User } from '@prisma/client';

@Injectable()
export class FriendPrismaService {
  constructor(private prisma: PrismaService) {}

  async getFriend(identifier: Prisma.FriendWhereUniqueInput): Promise<Friend> {
    return this.prisma.friend.findUnique({
      where: identifier,
    });
  }


  async getFriends(params: {
    skip?: number;
    take?: number;
    cursor?: Prisma.FriendWhereUniqueInput;
    where?: Prisma.FriendWhereInput;
    orderBy?: Prisma.FriendOrderByWithRelationInput;
    select?: {
        friend1_id: boolean;
        friend2_id: boolean;
        friend1: {
          select: {
            id: boolean;
            username: boolean;
            image: boolean;
            rating: boolean;
            available: boolean;
          }
        },
        friend2: {
          select: {
            id: boolean;
            username: boolean;
            image: boolean;
            rating: boolean;
            available: boolean;
          }
        },
      },
  }): Promise<Friend[]> {
    const { skip, take, cursor, where, orderBy } = params;
    return this.prisma.friend.findMany({
      skip,
      take,
      cursor,
      where,
      orderBy,
    });
  }

  /*	DBSetters_________________________________________________________________*/
  async createFriend(data: Prisma.FriendCreateInput): Promise<Friend> {
    return this.prisma.friend.create({ data });
  }

  async updateFriend(
    where: Prisma.FriendWhereUniqueInput,
    data: Prisma.FriendUpdateInput,
  ): Promise<Friend> {
    return this.prisma.friend.update({ data, where });
  }

  async deleteFriend(where: Prisma.FriendWhereUniqueInput): Promise<Friend> {
    return this.prisma.friend.delete({ where });
  }
}