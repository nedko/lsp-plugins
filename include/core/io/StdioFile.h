/*
 * StdlibFile.h
 *
 *  Created on: 6 мар. 2019 г.
 *      Author: sadko
 */

#ifndef INCLUDE_CORE_IO_STDIOFILE_H_
#define INCLUDE_CORE_IO_STDIOFILE_H_

#include <core/io/File.h>
#include <core/types.h>
#include <core/stdlib/stdio.h>
#include <core/io/Path.h>

namespace lsp
{
    namespace io
    {
        class StdioFile: public File
        {
            private:
                enum flags_t
                {
                    SF_READ     = 1 << 0,
                    SF_WRITE    = 1 << 1,
                    SF_CLOSE    = 1 << 2
                };

            protected:
                FILE       *pFD;
                size_t      nFlags;

            private:
                StdioFile &operator = (const StdioFile &fd);        // Deny copying

            public:
                explicit StdioFile();
                virtual ~StdioFile();

            public:
                /**
                 * Open file
                 * @param path file location
                 * @param mode open mode
                 * @return status of operation
                 */
                status_t    open(const char *path, size_t mode);

                /**
                 * Open file
                 * @param path file location
                 * @param mode open mode
                 * @return status of operation
                 */
                status_t    open(const LSPString *path, size_t mode);

                /**
                 * Open file
                 * @param path file location
                 * @param mode open mode
                 * @return status of operation
                 */
                status_t    open(const Path *path, size_t mode);

                /**
                 * Wrap the standard file descriptor and allow both read
                 * and write operations
                 * @param fd file descriptor to wrap
                 * @param close close the file descriptor on close() call
                 * @return status of operation
                 */
                status_t    wrap(FILE *fd, bool close);

                /**
                 * Wrap the standard file descriptor
                 * @param fd file descriptor to wrap
                 * @param mode allowed access modes (read, write or both)
                 * @param close close the file descriptor on close() call
                 * @return status of operation
                 */
                status_t    wrap(FILE *fd, size_t mode, bool close);

                /**
                 * Read binary file
                 * @param dst target buffer to perform read
                 * @param count amount of bytes to read
                 * @return number of bytes read or negative status of operation
                 */
                virtual ssize_t read(void *dst, size_t count);

                /**
                 * Perform positioned read of binary file
                 * @param pos offset in bytes relative to the beginning of the file
                 * @param dst target buffer to perform read
                 * @param count amount of bytes to read
                 * @return number of bytes read or status of operation
                 */
                virtual ssize_t pread(wsize_t pos, void *dst, size_t count);

                /**
                 * Write binary file
                 * @param dst source buffer to perform write
                 * @param count number of bytes to write
                 * @return number of bytes written or negative status of operation
                 */
                virtual ssize_t write(const void *src, size_t count);

                /**
                 * Perform positioned write of binary file
                 * @param pos offset in bytes relative to the beginning of the file
                 * @param dst source buffer to perform write
                 * @param count number of bytes to write
                 * @return status of operation
                 */
                virtual ssize_t pwrite(wsize_t pos, const void *src, size_t count);

                /**
                 * Perform seek to the specified position
                 * @param pos position to perform seek
                 * @param type seek type
                 * @return status of operation
                 */
                virtual status_t seek(wssize_t pos, size_t type);

                /**
                 * Obtain current file's position
                 * @return current file's position or negative error code
                 */
                virtual wssize_t position();

                /**
                 * Truncate the file
                 * @param length the final file length
                 * @return status of operation
                 */
                virtual status_t truncate(wsize_t length);

                /**
                 * Flush file buffer to underlying storage
                 * @return status of operation
                 */
                virtual status_t flush();

                /**
                 * Sync file with the underlying storage
                 * @return status of operation
                 */
                virtual status_t sync();

                /**
                 * Close file
                 * @return status of operation
                 */
                virtual status_t close();
        };
    
    } /* namespace io */
} /* namespace lsp */

#endif /* INCLUDE_CORE_IO_STDIOFILE_H_ */
