#ifndef CLSOCKETBASE_H
#define CLSOCKETBASE_H

#include <string>
#include <wx/sharedptr.h>
#include <wx/string.h>

#ifdef _WIN32
#include <winsock2.h>
typedef SOCKET socket_t;
typedef int socklen_t;
#else
typedef int socket_t;
#define INVALID_SOCKET -1
#endif

class clSocketException 
{
    std::string m_what;
public:
    clSocketException(const std::string & what ) : m_what(what) {}
    ~clSocketException() {}
    
    const std::string& what() const {
        return m_what;
    }
};

class clSocketBase
{
protected:
    socket_t m_socket;
public:
    typedef wxSharedPtr<clSocketBase> Ptr_t;
    
    enum {
        kSuccess = 1,
        kTimeout = 2,
        kError   = 3,
    };
    
    std::string error() const;
public:
    clSocketBase(int sockfd = INVALID_SOCKET);
    virtual ~clSocketBase();
    
    /**
     * @brief return the descriptor and clear this socket.
     */
    socket_t Release() ;
    
    /**
     * @brief initialize the socket library
     */
    static void Initialize();
    
    socket_t GetSocket() const {
        return m_socket;
    }
    
    /**
     * @brief 
     * @param msg
     */
    void Send(const std::string& msg) throw (clSocketException);
    /**
     * @brief 
     * @return 
     */
    int Read(char* buffer, size_t bufferSize, size_t& bytesRead, long timeout = -1) throw (clSocketException);
    /**
     * @brief 
     * @param milliseconds
     * @return 
     */
    int SelectRead(long seconds = -1) throw (clSocketException);

    /**
     * @brief read a full message that was sent with 'SendMessage' 
     * @param message
     * @param timeout seconds to wait
     * @return kSuccess, kTimeout or kError
     */
    int ReadMessage(wxString &message, int timeout) throw (clSocketException);
    
    /**
     * @brief write a full message
     * @param message
     */
    void WriteMessage(const wxString &message) throw (clSocketException);

protected:
    /**
     * @brief 
     */
    void CloseSocket();
};

#endif // CLSOCKETBASE_H
