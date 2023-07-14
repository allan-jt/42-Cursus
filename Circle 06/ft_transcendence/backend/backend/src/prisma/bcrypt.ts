import * as bcrypt from 'bcrypt'

export async function hashPassword(password: string): Promise<string> {
	const salt = await bcrypt.genSaltSync(10);
	return await bcrypt.hash(password, salt);
}

export async function comparePassword(
	password: string,
	hash: string,
): Promise<boolean> {
	return await bcrypt.compare(password, hash);
}