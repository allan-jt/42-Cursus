import { Injectable } from '@nestjs/common';
import { PrismaService } from './prisma.service';
import { Game, Prisma } from '@prisma/client';

@Injectable()
export class GamePrismaService {
  constructor(private prisma: PrismaService) {}

  async getGame(identifier: Prisma.GameWhereUniqueInput): Promise<Game> {
    return this.prisma.game.findUnique({
      where: identifier,
    });
  }

  async getGames(params: {
    skip?: number;
    take?: number;
    cursor?: Prisma.GameWhereUniqueInput;
    where?: Prisma.GameWhereInput;
    orderBy?: Prisma.GameOrderByWithRelationInput;
  }): Promise<Game[]> {
    const { skip, take, cursor, where, orderBy } = params;
    return this.prisma.game.findMany({
      skip,
      take,
      cursor,
      where,
      orderBy,
    });
  }

  /*	DBSetters_________________________________________________________________*/
  async createGame(data: Prisma.GameCreateInput): Promise<Game> {
    return this.prisma.game.create({ data });
  }

  async updateGame(
    where: Prisma.GameWhereUniqueInput,
    data: Prisma.GameUpdateInput,
  ): Promise<Game> {
    return this.prisma.game.update({ data, where });
  }

  async deleteGame(where: Prisma.GameWhereUniqueInput): Promise<Game> {
    return this.prisma.game.delete({ where });
  }
}
