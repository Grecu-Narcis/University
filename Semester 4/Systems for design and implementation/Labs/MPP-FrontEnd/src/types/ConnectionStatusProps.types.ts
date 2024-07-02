export type ConnectionStatusProps = {
    isOnline: boolean,
    setIsOnline: (newStatus: boolean) => void,
    isServerOnline: boolean,
    setIsServerOnline: (newStatus: boolean) => void,
    isLoggedIn: boolean,
    setIsLoggedIn: (newStatus: boolean) => void,
    handleLogout: () => void
}