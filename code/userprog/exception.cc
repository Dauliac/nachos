// exception.cc
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "userthread.h"

//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC ()
{
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions
//      are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler (ExceptionType which)
{
    int type = machine->ReadRegister (2);

    switch (which)
      {
      case SyscallException:
	  {
	      switch (type)
		{
		case SC_Halt:
		    {
			DEBUG ('s', "Shutdown, initiated by user program.\n");
			interrupt->Halt ();
			break;
		    }
#ifdef CHANGED
		case SC_PutChar:
		    {
			DEBUG ('s', "Put char, by user program.\n");
			semWriter->P ();
			char character = (char) machine->ReadRegister (4);
			synchconsole->SynchPutChar (character);
			semWriter->V ();
			break;
		    }

		case SC_PutString:
		    {
			// The test "result == MAX_STRING_SIZE"
			// do not work at the first iteration if the string is small than MAX_STRING_SIZE
			DEBUG ('s', "Put string, by user program.\n");
			semWriter->P ();
			int result = MAX_STRING_SIZE;
			int from = machine->ReadRegister (4);
			int i = 0;
			char *to = new char[MAX_STRING_SIZE];

			while (result == MAX_STRING_SIZE)
			  {
			      result =
				  synchconsole->copyStringFromMachine (from +
								       i, to,
								       MAX_STRING_SIZE);
			      synchconsole->SynchPutString (to);

			      i += result;
			  }
			delete[]to;
			semWriter->V ();
			break;
		    }

		case SC_GetChar:
		    {
			DEBUG ('s', "Get char, by user program.\n");
			semReader->P ();
			int result = synchconsole->SynchGetChar ();
			machine->WriteRegister (2, result);
			semReader->V ();
			break;
		    }

		case SC_GetString:
		    {
			DEBUG ('s', "Get string, by user program.\n");
			semReader->P ();
			int to = machine->ReadRegister (4);
			int i = 0;
			int result = MAX_STRING_SIZE;
			char *from = new char[MAX_STRING_SIZE];

			while (result == MAX_STRING_SIZE)
			  {
			      synchconsole->SynchGetString (from,
							    MAX_STRING_SIZE);
			      result =
				  synchconsole->copyStringToMachine (from,
								     to + i,
								     MAX_STRING_SIZE);
			      i += result;
			  }
			delete[]from;
			semReader->V ();
			break;
		    }

		case SC_PutInt:
		    {
			DEBUG ('s', "PutInt, by user program.\n");
			semWriter->P ();
			int result = machine->ReadRegister (4);
			synchconsole->SynchPutInt (result);
			semWriter->V ();
			break;
		    }

		case SC_ThreadCreate:
		    {
			DEBUG ('s', "Create thread, by user program.\n");
			semReader->P ();
			int function = machine->ReadRegister (4);
			int arg = machine->ReadRegister (5);
			int result = do_ThreadCreate (function, arg);
			DEBUG ('s', "Create thread return: %d.\n", result);
			machine->WriteRegister (2, result);
			semReader->P ();
			break;
		    }

		case SC_ThreadExit:
		    {
			DEBUG ('s', "Exit thread, by user program.\n");
			do_ThreadExit ();
			break;
		    }

#endif // CHANGED
		default:
		    {
			printf ("Unimplemented system call %d\n", type);
			ASSERT (FALSE);
		    }
		}

	      // Do not forget to increment the pc before returning!
	      UpdatePC ();
	      break;
	  }

      case PageFaultException:
	  if (!type)
	    {
		printf ("NULL dereference at PC %x!\n",
			machine->registers[PCReg]);
		ASSERT (FALSE);
	    }
	  else
	    {
		printf ("Page Fault at address %x at PC %x\n", type,
			machine->registers[PCReg]);
		ASSERT (FALSE);	// For now
	    }
	  break;

      default:
	  printf ("Unexpected user mode exception %d %d at PC %x\n", which,
		  type, machine->registers[PCReg]);
	  ASSERT (FALSE);
      }
}
