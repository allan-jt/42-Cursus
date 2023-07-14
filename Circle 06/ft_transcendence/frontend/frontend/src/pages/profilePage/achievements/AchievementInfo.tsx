
export interface AchievementInfo {
    id?: number
    achiev: string
    title: string,
    description: string
}

export const achievs: AchievementInfo[] = [
    {
        "id": 1,
        "achiev": "POWERPUFF_PADDLE",
        "title": "Powerpuff Paddle",
        "description": "Reach 1000+ rating"
    },
    {
        "id": 2,
        "achiev": "CHEMICAL_X_CHAMPION",
        "title": "Chemical X Champion",
        "description": "Win 3 games in a row"
    },
    {
        "id": 3,
        "achiev": "SUPER_SONIC_SERVE",
        "title": "Super Sonic Serve",
        "description": "Win 3 games in a day"
    },
    {
        "id": 4,
        "achiev": "VILLAIN_VANQUISHER",
        "title": "Villain Vanquisher",
        "description": "Win a game against a 'Powerpuff Paddle' with a rating < 1000"
    },
]

export default achievs;