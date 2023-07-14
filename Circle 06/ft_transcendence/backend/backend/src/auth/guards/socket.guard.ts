import { CanActivate, ExecutionContext, Injectable } from "@nestjs/common";
import { Socket } from "socket.io";
import { CookieService } from "src/cookie/cookie.service";
import { LoggedStrategyJWT } from "../passport/jwt.logged.strategy";

@Injectable()
export class SocketAuthGuard implements CanActivate {
	constructor(private cookieService: CookieService) {}
	
	async canActivate(context: ExecutionContext): Promise<boolean> {
		const client: Socket = context.switchToWs().getClient();
		const request = context.switchToHttp().getRequest();
		const jwtToken = LoggedStrategyJWT.extractJWTCookie(request);

		try {
			const payload = await this.cookieService.verifyJWTToken(jwtToken);
			request.user = payload;
			return true;
		} catch(err) {
			console.log("Token failed to authorize: ", err);
			client.disconnect();
			return false;
		}
	}
}