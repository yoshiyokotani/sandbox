/*This code is taken in part or in whole from boost library source.
  Tha appropriate licence information follows here: */

/*
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/


#if !defined(_TLS_HOOKS_H)
#define _TLS_HOOKS_H

#if defined(WIN32)

    void on_process_enter(void);
     /*   //Function to be called when the exe or dll
            //that uses Boost.Threads first starts
            //or is first loaded.
        //Should be called only before the first call to
            //on_thread_enter().
        //Called automatically by Boost.Threads when
            //a method for doing so has been discovered.
        //May be omitted; may be called multiple times.
    */
    
    void on_process_exit(void);
    /*    //Function to be called when the exe or dll
            //that uses Boost.Threads first starts
            //or is first loaded.
        //Should be called only after the last call to
            //on_exit_thread().
        //Called automatically by Boost.Threads when
            //a method for doing so has been discovered.
        //Must not be omitted; may be called multiple times.
    */

    void on_thread_enter(void);
    /*    //Function to be called just after a thread starts
            //in an exe or dll that uses Boost.Threads.
        //Must be called in the context of the thread
            //that is starting.
        //Called automatically by Boost.Threads when
            //a method for doing so has been discovered.
        //May be omitted; may be called multiple times.
    */
    
    void on_thread_exit(void);
    /*    //Function to be called just be fore a thread ends
            //in an exe or dll that uses Boost.Threads.
        //Must be called in the context of the thread
            //that is ending.
        //Called automatically by Boost.Threads when
            //a method for doing so has been discovered.
        //Must not be omitted; may be called multiple times.
    */

    void tss_cleanup_implemented(void);
    /*        //Dummy function used both to detect whether tss cleanup
            //cleanup has been implemented and to force
            //it to be linked into the Boost.Threads library.
    */
#endif //#ifdef(WIN32)
#endif //!defined(_TLS_HOOKS_H)
